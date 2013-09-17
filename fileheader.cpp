#include "fileheader.h"

FileHeader::FileHeader()
{
}

FileHeader::~FileHeader()
{
}

void FileHeader::addField(Field* field)
{
    this->fields.push_back(field);
}

void FileHeader::modifyField(int n, Field* field)
{
    this->fields.at(n)->setName(field->getName());
    if(field->isKey()){
        for(int i = 0; i < this->fields.size(); i++){
            if(this->fields.at(i)->isKey()){
                this->fields.at(i)->setKey(0);
                i = this->fields.size();
            }
        }
        this->fields.at(n)->setKey(1);
    }
    delete field;
}

void FileHeader::removeField(int n)
{
    this->fields.erase(this->fields.begin() + n);
}

Field* FileHeader::getField(int n)
{
    return this->fields.at(n);
}

string FileHeader::toString() const
{
    stringstream ss;
    ss<<'$';
    for(size_t i = 0; i < this->fields.size(); i++){
        ss<<this->fields.at(i)->getName()<<','
         <<this->fields.at(i)->getType()<<',';

        if(this->fields.at(i)->isKey()){
            ss<<'1';
        }else{
            ss<<'0';
        }

        ss<<this->fields.at(i)->getLength()<<','
         <<this->fields.at(i)->getDecimalPlaces();

        if(i < fields.size() -1){
            ss<<'/';
        }
    }
    ss<<'$';
}

int FileHeader::fieldsSize() const{
    return this->fields.size();
}

vector<Field*> FileHeader::getFields()
{
    return this->fields;
}
