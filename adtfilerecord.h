#ifndef ADTFILERECORD_H
#define ADTFILERECORD_H

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
    void setDataStart(int);
    void setRecordLength(int);
    void readHeader(char*);
    FileHeader* getFileHeader();
    virtual int getDataStart();

private:
    int recordLength;
    int dataStart;

    FileHeader* header;
    string fileName;
    fstream FS;
    QStack<int> AvailList;
};

#endif // ADTFILERECORD_H
