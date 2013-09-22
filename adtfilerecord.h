#ifndef ADTFILERECORD_H
#define ADTFILERECORD_H

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

class ADTFileRecord:public ADTFile
{
public:    
    ADTFileRecord();
    ADTFileRecord(string, int);
    virtual ~ADTFileRecord();

    //metodos no utilizados
    //virtual void seekgRecord(int);
    //virtual void seekpRecord(int);
    //virtual string readRecord(int);
    //virtual bool writeRecord(string);
    //virtual bool updateRecord(int, string);
    //virtual bool deleteRecord(int);
    //virtual void compact();

    //metodos utilizados para campos y registros
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
    //bool deleteRecord(string);
    void insertIndex(string, PrimaryIndex*);

private:
    int recordLength;
    streamoff dataStart;
    string fileName;
    //fstream FS;

    QMap<QString,PrimaryIndex*> indexes;
    QStack<streamoff> AvailList;
    vector<Field*> fields;
};

#endif // ADTFILERECORD_H
