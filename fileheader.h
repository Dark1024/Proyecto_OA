#ifndef FILEHEADER_H
#define FILEHEADER_H

#include <string>
#include <vector>
#include <sstream>

#include "field.h"

using namespace std;

class FileHeader
{
public:
    FileHeader();
    ~FileHeader();

    void addField(Field*);
    void modifyField(int,Field*);
    void removeField(int);
    Field* getField(int);
    string toString() const;
    int fieldsSize() const;
    vector<Field*> getFields();
private:
    vector<Field*> fields;
};

#endif // FILEHEADER_H
