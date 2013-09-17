#include "primaryindex.h"

PrimaryIndex::PrimaryIndex(string Key, streamoff Offset):Object()
{
    this->key = Key;
    this->offset = Offset;
}

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
