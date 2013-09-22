#include "adtfilerecord.h"

ADTFileRecord::ADTFileRecord():ADTFile()
{
    this->fileName = "";
    this->recordLength = 0;
}

ADTFileRecord::ADTFileRecord(string Name,int recordLength):ADTFile()
{
    this->fileName = Name;
    this->recordLength = recordLength;
}

ADTFileRecord::~ADTFileRecord()
{
    this->FS.flush();
    this->FS.close();
}

/*void ADTFileRecord::seekgRecord(int recordNumber)
{
    this->FS.seekg(this->dataStart + ((recordNumber-1) * this->recordLength));
}

void ADTFileRecord::seekpRecord(int recordNumber)
{
    this->FS.seekp(this->dataStart + ((recordNumber-1) * this->recordLength));
}

string ADTFileRecord::readRecord(int recordNumber)
{
    char* tmp = new char[this->recordLength];
    this->seekgRecord(recordNumber);
    this->FS.read(tmp,this->recordLength);
    string str(tmp);
    return str;
}

bool ADTFileRecord::writeRecord(string record)
{
    if(record.length() != this->recordLength){
        return false;
    }

    if(this->AvailList.isEmpty()){
        FS.seekp(0,ios_base::end);
        FS.write(record.c_str(),this->recordLength);
        return !FS.fail();
    }else{
        this->seekpRecord(this->AvailList.pop());
        this->FS.write(record.c_str(),this->recordLength);
    }
    return !FS.fail();
}

bool ADTFileRecord::updateRecord(int recordNumber, string record)
{
    if(record.length() != this->recordLength){
        return false;
    }

    this->seekpRecord(recordNumber);
    FS.write(record.c_str(),this->recordLength);
    return !FS.fail();
}

bool ADTFileRecord::deleteRecord(int recordNumber)
{
    this->seekpRecord(recordNumber);
    string mark = "*";

    FS.write(mark.c_str(),mark.length());

    if(FS.fail())
        return false;
    this->AvailList.push(recordNumber);
    return true;
}
*/

void ADTFileRecord::setDataStart(streamoff dataStart)
{
    this->dataStart = dataStart;
}

void ADTFileRecord::setRecordLength(int recordLength)
{
    this->recordLength = recordLength;
}

void ADTFileRecord::readHeader(char* header)
{
    char* c;
    vector<char*> tmpFields;

    c = strtok(header,"/");
    tmpFields.push_back(c);
    while(c != NULL){
        c = strtok(NULL,"/");
        tmpFields.push_back(c);
    }

    for(int i = 0; i < tmpFields.size()-1; i++){
        string name = strtok(tmpFields[i],",");
        char Type = strtok(NULL,",")[0];
        int key = atoi(strtok(NULL,","));
        int length = atoi(strtok(NULL,","));
        int decimal = atoi(strtok(NULL,","));

        Field* newField = new Field(name, Type, key, length, decimal);

        this->addField(newField);
    }
}

streamoff ADTFileRecord::getDataStart()
{
    return this->dataStart;
}

void ADTFileRecord::addField(Field* field)
{
    this->fields.push_back(field);
}

void ADTFileRecord::modifyField(int n, Field* field)
{
    this->fields.at(n)->setName(field->getName());
    if(field->isKey()){
        for(int i = 0; i < this->fields.size(); i++){
            if(this->fields.at(i)->isKey()){
                this->fields.at(i)->setKey(0);
                i = this->fields.size();
            }
        }
        this->fields.at(n)->setKey(1);
    }
    delete field;
}

void ADTFileRecord::removeField(int n)
{
    this->fields.erase(this->fields.begin() + n);
}

string ADTFileRecord::toStringHeader()
{
    stringstream ss;
    ss<<'$';
    for(size_t i = 0; i < this->fields.size(); i++){
        ss<<this->fields.at(i)->getName()<<','
         <<this->fields.at(i)->getType()<<',';

        if(this->fields.at(i)->isKey()){
            ss<<'1';
        }else{
            ss<<'0';
        }
        ss<<',';
        ss<<this->fields.at(i)->getLength()<<','
         <<this->fields.at(i)->getDecimalPlaces();

        if(i < fields.size() -1){
            ss<<'/';
        }
    }
    ss<<'$';
    return ss.str();
}

vector<Field*> ADTFileRecord::getFields()
{
    return this->fields;
}

int ADTFileRecord::fieldsSize()
{
    return this->fields.size();
}

Field* ADTFileRecord::getField(int n)
{
    return this->fields.at(n);
}

bool ADTFileRecord::addRecord(Record* record)
{
    if(!this->isOpen()){
        return false;
    }

    vector<Field*> tmpfields = record->getFields();
    vector<string> tmprecord = record->getRecord();
    stringstream ss;

    for (int i = 0; i < tmpfields.size(); i++){
        Field* tmpcurrentField = tmpfields.at(i);
        if(tmpcurrentField->isKey()){
            string str = tmprecord.at(i);
            ss<<str;
        }
    }

    QString key = QString::fromStdString(ss.str());

    if(this->indexes.contains(key)){
        return false;
    }

    streamoff offset;
    if(this->AvailList.isEmpty()){
        this->seekp(0,ios_base::end);
        offset = this->tellp();
    }else{
        this->seekp(this->AvailList.pop(),ios_base::beg);
        offset = this->tellp();
    }

    streamoff length = record->toString().size();

    this->write(record->toString().c_str(),length);

    if(this->isOk()){
        this->indexes.insert(key,new PrimaryIndex(key.toStdString(),offset));
    }else{
        return false;
    }

    return true;
}

vector<PrimaryIndex*> ADTFileRecord::getIndexes()
{
    return this->indexes.values().toVector().toStdVector();
}

bool ADTFileRecord::indexesIsEmpty()
{
    if(this->indexes.isEmpty())
        return true;
    return false;
}

Record* ADTFileRecord::getRecord(PrimaryIndex* pi)
{
    if(!this->isOpen()){
        return NULL;
    }

    this->FS.seekg(pi->getOffset(),ios_base::beg);
    this->FS.seekp(pi->getOffset(),ios_base::beg);

    char* tmp = new char[this->recordLength + 1];

    streamoff rl = this->recordLength;
    this->FS.read(tmp,rl);
    tmp[this->recordLength] = '\0';

    string str (tmp);
    QString qstr = QString::fromStdString(str);
    vector<string> record;

    int counter = 0;
    for(int i = 0; i < this->fields.size(); i++){
        Field* currentField = fields.at(i);

        QString qstr2 = qstr.mid(counter,currentField->getLength());

        cout<<qstr2.toStdString()<<endl;

        qstr2 = qstr2.replace("_"," ");

        record.push_back(qstr2.toStdString());

        counter += currentField->getLength();
    }

    Record* newRecord = new Record(this->fields,record);
    return newRecord;
}

void ADTFileRecord::insertIndex(string key, PrimaryIndex* index)
{
    this->indexes.insert(QString::fromStdString(key),index);
}

PrimaryIndex* ADTFileRecord::searchRecord(string key)
{
    if(!this->isOpen()){
        return NULL;
    }

    if(!this->indexes.contains(QString::fromStdString(key))){
        return NULL;
    }

    return this->indexes.value(QString::fromStdString(key));
}
