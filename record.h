#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

#include "field.h"

using namespace std;

class Record
{
public:
    Record(vector<Field*>, vector<string>);
    ~Record();
    string toString() const;
    vector<Field*> getFields() const;
    vector<string> getRecord() const;
private:
    vector<Field*> fields;
    vector<string> record;
};

#endif // RECORD_H
