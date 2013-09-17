#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <sstream>

using namespace std;

class Field
{
public:
    Field();
    Field(string = "", char = ' ', int = 0, int = 0, int = 0);
    ~Field();
    string getName() const;
    void setName(string);
    char getType() const;
    void setType(char);
    bool isKey() const;
    void setKey(int);
    int getLength() const;
    void setLength(int);
    int getDecimalPlaces() const;
    void setDecimalPlaces(int);
    string toString() const;

private:
    string Name;
    char Type;
    int Key;
    int Length;
    int Decimals;
};

#endif // FIELD_H
