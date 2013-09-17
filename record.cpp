#include "record.h"

Record::Record(vector<Field*> fields, vector<string> record)
{
    this->fields = fields;
    this->record = record;
}

string Record::toString() const
{
    return "";
}

vector<Field*> Record::getFields() const
{
    return this->fields;
}

vector<string> Record::getRecord() const
{
    return this->record;
}
