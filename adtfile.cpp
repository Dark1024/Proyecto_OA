#include "adtfile.h"

//Constructor

ADTFile::ADTFile()
{
}

//Destructor

ADTFile::~ADTFile()
{
    this->FS.close();
}

//Mutadores y accesores

//Abre un nuevo archivo y guarda su direccion y su tipo de abertura
bool ADTFile::open(string Path, ios_base::openmode flags)
{
    this->Nombre = Path;
    this->flags = flags;
    this->FS.open(this->Nombre.c_str(), this->flags);
    return this->isOpen();
}

//Cierra el archivo
bool ADTFile::close()
{
    this->FS.close();
    return !this->isOpen();
}

//Mueve el puntero de lectura en el archivo hasta la posicion indicada
bool ADTFile::seekg(streamoff n, ios_base::seekdir flags)
{
    this->FS.seekg(n,flags);
    return this->FS.good();
}

//Mueve el puntero de escritura en el archivo hasta la posicion indicada
bool ADTFile::seekp(streamoff n, ios_base::seekdir flags)
{
    this->FS.seekp(n,flags);
    return this->FS.good();
}

//Retorna el lugar donde esta el puntero de lectura del archivo
streamoff ADTFile::tellg()
{
    return this->FS.tellg();
}

//Retorna el lugar donde esta el puntero de escritura del archivo
streamoff ADTFile::tellp(){
    return this->FS.tellp();
}

//Lee el contenido del archivo
int ADTFile::read(char* str, streamoff n)
{
    if(this->isOpen()){
        this->FS.read(str,n);
        str[n+1] = '\0';
        return FS.gcount();
    }else{
        return -1;
    }
}

//Escribe dentro del archivo el buffer que recibe
int ADTFile::write(const char* str, streamoff n){
    if(this->isOpen()){
        this->FS.write(str,n);
        return this->FS.gcount();
    }else{
        return -1;
    }
}

//Verifica si el archivo esta abierto o no
bool ADTFile::isOpen() const
{
    return this->FS.is_open();
}

//Verifica si estamos en el final del archivo
bool ADTFile::isEOF() const
{
    if(this->isOpen()){
        return this->FS.eof();
    }else{
        return false;
    }
}

//Verifica si estamos en el principio del archivo
bool ADTFile::isBOF() const
{
    bool retval = false;
    if(this->isOpen()){

    }
    return retval;
}

//Ordena al sistema operativo que escriba todos las escrituras en el archivo
bool ADTFile::flush()
{
    if(!this->isOpen()){
        return false;
    }
    return !this->FS.flush().fail();
}

//Verifica que el archivo esta en buenas condiciones
bool ADTFile::isOk()
{
    return this->FS.good();
}

//Retorna la direccion especifica del archivo que se guarda en la clase
string ADTFile::getFileName()
{
    return this->Nombre;
}
