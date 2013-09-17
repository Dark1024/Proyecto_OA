#include "adtfilerecord.h"

ADTFileRecord::ADTFileRecord():ADTFile()
{
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

void ADTFileRecord::seekgRecord(int recordNumber)
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

void ADTFileRecord::setDataStart(int dataStart)
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

FileHeader* ADTFileRecord::getFileHeader()
{
    return this->header;
}

int ADTFileRecord::getDataStart()
{
    return this->dataStart;
}

void ADTFileRecord::addField(Field* field)
{
    this->fields.push_back(field);
}

void ADTFileRecord::modifyField(int n, Field* field)
{
    this->fields.at(n).setName(field->getName());
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

string ADTFileRecord::toStringHeader() const
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

        ss<<this->fields.at(i)->getLength()<<','
         <<this->fields.at(i)->getDecimalPlaces();

        if(i < fields.size() -1){
            ss<<'/';
        }
    }
    ss<<'$';
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
