#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

//Importacion de encazados necesarios
#include <string>
#include <sstream>

#include "object.h"

using namespace std;

/***********************************************************************
 *Clase que se utiliza para manejar los indices primarios del archivo de
 *registro, permiten una busqueda rapida y son de mucha ayuda en la
 *lectura de registros
 **********************************************************************
 */
class PrimaryIndex:public Object
{
public:
    //Constructor
    PrimaryIndex(string = "", streamoff = 0);
    ~PrimaryIndex();
    //Mutadores y accesores
    const string getKey() const;
    const streamoff getOffset() const;
    virtual bool operator == (const PrimaryIndex&);

    //toString
    string toString();

    //caracteristicas privadas
private:
    string key;
    streamoff offset;
};

#endif // PRIMARYINDEX_H
