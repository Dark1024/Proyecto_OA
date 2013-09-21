#include "record.h"

Record::Record(vector<Field*> fields, vector<string> record)
{
    this->fields = fields;
    this->record = record;
}

Record::~Record()
{
}

string Record::toString() const
{
    stringstream ss;
    for(int i = 0; i < this->fields.size(); i++){
        for(int j = 0; j < (fields[i]->getLength() - record[i].size()); j++){
            ss<<'_';
        }
        ss<<record.at(i);
    }

    return ss.str();
}

vector<Field*> Record::getFields() const
{
    return this->fields;
}

vector<string> Record::getRecord() const
{
    return this->record;
}
