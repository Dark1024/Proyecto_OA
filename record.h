#ifndef RECORD_H
#define RECORD_H

//Importacion de encabezados necesarios
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

#include "field.h"

using namespace std;

/****************************************************************
 *Clase importante para la manipulacion de los registros
 *que estan contenidos en el archivo, pues maneja dos
 *vectores de la misma longitud que mantiene una correspondencia
 *entra cada uno de elementos de cada vector
 ****************************************************************
 */
class Record
{
public:
    //Constructor y destructor
    Record(vector<Field*>, vector<string>);
    ~Record();

    //toString
    string toString() const;

    //Accesores
    vector<Field*> getFields() const;
    vector<string> getRecord() const;

    //caracteristicas privadas
private:
    vector<Field*> fields;
    vector<string> record;
};

#endif // RECORD_H
