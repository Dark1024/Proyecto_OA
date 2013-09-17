#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include <string>

#include "object.h"

using namespace std;

class PrimaryIndex:public Object
{
public:
    PrimaryIndex(string = "", streamoff = 0);
    const string getKey() const;
    const streamoff getOffset() const;
    virtual bool operator == (const PrimaryIndex&);
private:
    string key;
    streamoff offset;
};

#endif // PRIMARYINDEX_H
