#include "adtfile.h"

ADTFile::ADTFile()
{
}

ADTFile::~ADTFile()
{
    this->FS.close();
}

bool ADTFile::open(string Path, ios_base::openmode flags)
{
    this->Nombre = Path;
    this->flags = flags;
    this->FS.open(this->Nombre.c_str(), this->flags);
    return this->isOpen();
}

bool ADTFile::close()
{
    this->FS.close();
    return !this->isOpen();
}

bool ADTFile::seekg(streamoff n, ios_base::seekdir flags)
{
    this->FS.seekg(n,flags);
    return this->FS.good();
}

bool ADTFile::seekp(streamoff n, ios_base::seekdir flags)
{
    this->FS.seekp(n,flags);
    return this->FS.good();
}

streamoff ADTFile::tellg()
{
    return this->FS.tellg();
}

streamoff ADTFile::tellp(){
    return this->FS.tellp();
}

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

int ADTFile::write(const char* str, streamoff n){
    if(this->isOpen()){
        this->FS.write(str,n);
        return this->FS.gcount();
    }else{
        return -1;
    }
}

bool ADTFile::isOpen() const
{
    return this->FS.is_open();
}

bool ADTFile::isEOF() const
{
    if(this->isOpen()){
        return this->FS.eof();
    }else{
        return false;
    }
}

bool ADTFile::isBOF() const
{
    bool retval = false;
    if(this->isOpen()){

    }
    return retval;
}

bool ADTFile::flush()
{
    if(!this->isOpen()){
        return false;
    }
    return !this->FS.flush().fail();
}

bool ADTFile::isOk()
{
    return this->FS.good();
}
