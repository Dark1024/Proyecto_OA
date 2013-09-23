#include "primaryindex.h"

//Constructor, contiene una llave primaria y un offset del archivo
PrimaryIndex::PrimaryIndex(string Key, streamoff Offset):Object()
{
    this->key = Key;
    this->offset = Offset;
}

//Destructor de la clase
PrimaryIndex::~PrimaryIndex()
{
}

//Accesores
const string PrimaryIndex::getKey() const
{
    return this->key;
}

const streamoff PrimaryIndex::getOffset() const
{
    return this->offset;
}

bool PrimaryIndex::operator ==(const PrimaryIndex& pindex)
{
    return this->key == pindex.key;
}

//toString de la clase
string PrimaryIndex::toString()
{
    stringstream ss;
    ss<<this->key<<','<<this->getOffset();
    return ss.str();
}
