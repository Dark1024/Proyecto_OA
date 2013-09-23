#ifndef ADTFILE_H
#define ADTFILE_H

//Incluir los encabezados necesarios
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//Clase ADTFile que maneja un fstream y todas sus operaciones
class ADTFile
{
    //Metodos publicos
public:
    //Constructor y destructor
    ADTFile();
    virtual ~ADTFile();

    //Mutadores y accesores
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
    virtual string getFileName();

    //Caracteristicas Protected para que sus hijos puedan acceder a estos
protected:
    string Nombre;
    fstream FS;
    ios_base::openmode flags;
};

#endif // ADTFILE_H
