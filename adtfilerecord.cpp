#include "adtfilerecord.h"

//Constructores y destructor

ADTFileRecord::ADTFileRecord():ADTFile()
{
    this->fileName = "";
    this->recordLength = 0;
}

//Constructor sobrecargado de la clase
ADTFileRecord::ADTFileRecord(string Name,int recordLength):ADTFile()
{
    this->fileName = Name;
    this->recordLength = recordLength;
}

//Destructor de la clase;
ADTFileRecord::~ADTFileRecord()
{
    this->FS.flush();
    this->FS.close();
}

//Mutadores y accesores

//Asigna el inicio de la data de este archivo
void ADTFileRecord::setDataStart(streamoff dataStart)
{
    this->dataStart = dataStart;
}

//Asigna el tamanio de los registros guardados en el archivo
void ADTFileRecord::setRecordLength(int recordLength)
{
    this->recordLength = recordLength;
}

//Metodo que lee el header a partir del contenido del archivo
//Se encarga de cargar los campos contenidos dentro de este
void ADTFileRecord::readHeader(char* header)
{
    char* c;
    vector<char*> tmpFields;

    //Se utiliza strtok para separar a partir del valor "/"
    c = strtok(header,"/");
    tmpFields.push_back(c);
    while(c != NULL){
        c = strtok(NULL,"/");
        tmpFields.push_back(c);
    }

    //Se crean los campos a partir de los arreglos de caracteres obtenidos
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

//Retorna el inicio de la data del archivo
streamoff ADTFileRecord::getDataStart()
{
    return this->dataStart;
}

//Se agrega un nuevo campo al vector de campos manejados por el archivo
void ADTFileRecord::addField(Field* field)
{
    this->fields.push_back(field);
}

//Se encarga de modicar ciertos atributos de un campo ya existente
void ADTFileRecord::modifyField(int n, Field* field)
{
    //Se cambia solamente el nombre y el hecho de ser llave primaria
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
    //Elimina el campo que ya no es necesario
    delete field;
}

//Remueve un campo del vector de campos
void ADTFileRecord::removeField(int n)
{
    this->fields.erase(this->fields.begin() + n);
}

//String especial utilizado para guardar un formato especial del header
//que se escribe en el archivo que se utiliza
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

//Retorna un vector de campos que contiene el archivo
vector<Field*> ADTFileRecord::getFields()
{
    return this->fields;
}

//Retorna el tamanio del vector de campos que contiene el archivo
int ADTFileRecord::fieldsSize()
{
    return this->fields.size();
}

//Retorna un campo especifico del vector de campos que contiene el archivo
Field* ADTFileRecord::getField(int n)
{
    return this->fields.at(n);
}

//Encargado de agregar un nuevo registro al archivo
bool ADTFileRecord::addRecord(Record* record)
{
    //verifica si el archivo esta abierto
    if(!this->isOpen()){
        return false;
    }

    //obtiene los vectores del registro
    vector<Field*> tmpfields = record->getFields();
    vector<string> tmprecord = record->getRecord();
    stringstream ss;

    //Obtiene la llave primaria del registro
    for (int i = 0; i < tmpfields.size(); i++){
        Field* tmpcurrentField = tmpfields.at(i);
        if(tmpcurrentField->isKey()){
            string str = tmprecord.at(i);
            ss<<str;
        }
    }

    QString key = QString::fromStdString(ss.str());

    //verifica si la llave primaria ya existe
    if(this->indexes.contains(key)){
        return false;
    }

    //Toma el lugar donde ira a guardar el registro dentro del archivo
    streamoff offset;
    if(this->AvailList.isEmpty()){
        this->seekp(0,ios_base::end);
        offset = this->tellp();
    }else{
        this->seekp(this->AvailList.pop(),ios_base::beg);
        offset = this->tellp();
    }

    //Toma el tamanio del registro para tomar la cantidad de caracteres a guardar
    streamoff length = record->toString().size();

    //Escribe dentro del archivo el nuevo registro
    this->write(record->toString().c_str(),length);

    //verifica si todo esta bien dentro del archivo
    if(this->isOk()){
        //inserta el indice primario en el mapa de indices
        this->indexes.insert(key,new PrimaryIndex(key.toStdString(),offset));
    }else{
        return false;
    }

    return true;
}

//Obtiene todos los indices primarios que contiene el archivo de indices
vector<PrimaryIndex*> ADTFileRecord::getIndexes()
{
    return this->indexes.values().toVector().toStdVector();
}

//Verifica si el mapa de indices primarios esta vacio
bool ADTFileRecord::indexesIsEmpty()
{
    if(this->indexes.isEmpty())
        return true;
    return false;
}

//Lee un registro a partir de los indices primarios
Record* ADTFileRecord::getRecord(PrimaryIndex* pi)
{
    //verifica si el archivo esta abierto
    if(!this->isOpen()){
        return NULL;
    }

    //mueve los punteros de lectura y escritura
    this->FS.seekg(pi->getOffset(),ios_base::beg);
    this->FS.seekp(pi->getOffset(),ios_base::beg);

    //creacion del buffer para la lectura
    char* tmp = new char[this->recordLength + 1];

    streamoff rl = this->recordLength;
    this->FS.read(tmp,rl);
    tmp[this->recordLength] = '\0';

    //convierte el buffer a un QString
    string str (tmp);
    QString qstr = QString::fromStdString(str);
    vector<string> record;

    //Obtiene uno por uno los datos del registro uno por cada campo
    //Lo hace a partir de substrings dentro de la cadena resultante de la lectura
    int counter = 0;
    for(int i = 0; i < this->fields.size(); i++){
        Field* currentField = fields.at(i);

        QString qstr2 = qstr.mid(counter,currentField->getLength());

        qstr2 = qstr2.replace("_"," ");

        record.push_back(qstr2.toStdString());

        counter += currentField->getLength();
    }

    //creacion de un nuevo registro y lo retorna
    Record* newRecord = new Record(this->fields,record);
    return newRecord;
}

//Inserta en el mapa de indices primarios uno nuevo
void ADTFileRecord::insertIndex(string key, PrimaryIndex* index)
{
    this->indexes.insert(QString::fromStdString(key),index);
}

//Busca una llave primaria dentro del mapa de los indices primarios
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

//Borra un registro del archivo, lo marca para luego compactar el archivo
//Ademas elimina su indice primario para poder sobreescribir en el lugar
bool ADTFileRecord::deleteRecord(PrimaryIndex* index)
{
    streamoff offset = index->getOffset();

    this->FS.seekp(offset,ios_base::beg);
    char* tmp = "*";
    this->FS.write(tmp,1);

    this->FS.flush();


    if(this->indexes.remove(QString::fromStdString(index->getKey())) == 0 ){
        return false;
    }

    //Ingresa el offset ahora disponible para poder reescribir en el lugar
    this->AvailList.push_back(offset);
    return true;
}

//Limpia todo el mapa de indices primarios
void ADTFileRecord::cleanMap()
{
    while(this->indexes.size() != 0){
        this->indexes.clear();
    }
}
