#ifndef ADTFILERECORD_H
#define ADTFILERECORD_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QStack>
#include <iostream>

#include "adtfile.h"
#include "fileheader.h"

using namespace std;

class ADTFileRecord:public ADTFile
{
public:
    ADTFileRecord();
    ADTFileRecord(string, int);
    virtual ~ADTFileRecord();
    virtual void seekgRecord(int);
    virtual void seekpRecord(int);
    virtual string readRecord(int);
    virtual bool writeRecord(string);
    virtual bool updateRecord(int, string);
    virtual bool deleteRecord(int);
    //virtual void compact();
    virtual void setDataStart(int);
    virtual void setRecordLength(int);
    virtual void readHeader(char*);
    virtual int getDataStart();
    virtual void addField(Field*);
    virtual void modifyField(int, Field*);
    virtual void removeField(int);
    virtual Field* getField(int);
    virtual string toStringHeader() const;
    virtual int fieldsSize() const;
    vector<Field*> getFields();

private:
    int recordLength;
    int dataStart;

    string fileName;
    fstream FS;
    QStack<int> AvailList;
    vector<Field*> fields;
};

#endif // ADTFILERECORD_H
