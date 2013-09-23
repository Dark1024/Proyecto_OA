#ifndef ADTFILERECORD_H
#define ADTFILERECORD_H

//Importacion de encabezados necesarios
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QStack>
#include <QMap>
#include <QString>
#include <iostream>
#include <ostream>

#include "adtfile.h"
#include "field.h"
#include "primaryindex.h"
#include "record.h"

using namespace std;

/**************************************************
 *Clase ADTFileRecord, descendiente de ADTFile
 *Contiene metodos extras necesarios para manipular
 *los archivos especiales del programa
 **************************************************
*/

class ADTFileRecord:public ADTFile
{
    //Metodos publicos de la clase
public:
    //Constructores y destructor
    ADTFileRecord();
    ADTFileRecord(string, int);
    virtual ~ADTFileRecord();

    //Mutadores y accesores
    void setDataStart(streamoff);
    void setRecordLength(int);
    void readHeader(char*);
    streamoff getDataStart();
    void addField(Field*);
    void modifyField(int, Field*);
    void removeField(int);
    Field* getField(int);
    string toStringHeader();
    int fieldsSize();
    vector<Field*> getFields();
    vector<PrimaryIndex*> getIndexes();
    bool addRecord(Record*);
    bool indexesIsEmpty();
    Record* getRecord(PrimaryIndex*);
    PrimaryIndex* searchRecord(string);
    bool deleteRecord(PrimaryIndex*);
    void insertIndex(string, PrimaryIndex*);
    void cleanMap();

    //Caracteristicas privadas de la clase
private:
    int recordLength;
    streamoff dataStart;
    string fileName;

    QMap<QString,PrimaryIndex*> indexes;
    QStack<streamoff> AvailList;
    vector<Field*> fields;
};

#endif // ADTFILERECORD_H
