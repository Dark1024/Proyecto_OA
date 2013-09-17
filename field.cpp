#include "field.h"

Field::Field()
{
    this->Name = "";
    this->Type = ' ';
    this->Key = 0;
    this->Length = 0;
    this->Decimals = 0;
}

Field::Field(string Name, char Type, int Key, int Length, int Decimals)
{
    this->Name = Name;
    this->Type = Type;
    this->Key = Key;
    this->Length = Length;
    this->Decimals = Decimals;
}

Field::~Field()
{
}

string Field::getName() const
{
    return this->Name;
}

void Field::setName(string Name)
{
    this->Name = Name;
}

char Field::getType() const
{
    return this->Type;
}

void Field::setType(char Type)
{
    this->Type = Type;
}

bool Field::isKey() const
{
    if(this->Key == 1)
        return true;
    return false;
}

void Field::setKey(int Key)
{
    this->Key = Key;
}

int Field::getLength() const
{
    return this->Length;
}

void Field::setLength(int Length)
{
    this->Length = Length;
}

int Field::getDecimalPlaces() const
{
    return this->Decimals;
}

void Field::setDecimalPlaces(int Decimals)
{
    this->Decimals = Decimals;
}

string Field::toString() const{
    stringstream ss;
    ss<<this->Name<<','
    <<this->Type<<','
    <<this->Key<<','
    <<this->Length<<','
    <<this->Decimals;
    return ss.str();
}
