#ifndef OBJECT_H
#define OBJECT_H

#include <string>

using namespace std;

/******************************************************
 *Clase creada con el unico fin de poder simular una
 *clase object de la cual se pueda heredar, para facilitar
 *el uso del arbol b
 */
class Object
{
public:
    //Constructor y toString
    Object();
    virtual string toString() const;
};

#endif // OBJECT_H
