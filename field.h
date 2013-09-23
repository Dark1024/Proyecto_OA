#ifndef FIELD_H
#define FIELD_H

//Importar los encabezados necesarios
#include <string>
#include <sstream>

using namespace std;

/********************************************
 *Clase que contiene los datos principales de
 *un campo y que sirven de parametros de los
 *registros del todo el archivo
 */
class Field
{
    //Metodos publicos de la clase
public:
    //Constructores y destructores
    Field();
    Field(string = "", char = ' ', int = 0, int = 0, int = 0);
    ~Field();

    //Mutadores y accesores
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

    //toString
    string toString() const;

    //Caracteristicas privadas de la clase
private:
    string Name;
    char Type;
    int Key;
    int Length;
    int Decimals;
};

#endif // FIELD_H
