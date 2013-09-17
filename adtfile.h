#ifndef ADTFILE_H
#define ADTFILE_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ADTFile
{
public:
    ADTFile();
    virtual ~ADTFile();
    virtual bool open(string = "", ios_base::openmode = ios_base::in | ios_base::out);
    virtual bool close();
    virtual bool seekg(streamoff, ios_base::seekdir);
    virtual bool seekp(streamoff, ios_base::seekdir);
    virtual streamoff tellg();
    virtual streamoff tellp();
    virtual int read(char*, streamoff);
    virtual int write(const char*, streamoff);
    virtual bool isOpen() const;
    virtual bool isEOF() const;
    virtual bool isBOF() const;
    virtual bool flush();
    virtual bool isOk();

protected:
    string Nombre;
    fstream FS;
    ios_base::openmode flags;
};

#endif // ADTFILE_H
