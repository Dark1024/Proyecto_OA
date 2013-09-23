#ifndef MODIFYFIELDWINDOW_H
#define MODIFYFIELDWINDOW_H

//Importacion de encabezados necesarios
#include <QDialog>
#include <QMessageBox>
#include <vector>
#include <QString>

#include "field.h"

namespace Ui {
class ModifyFieldWindow;
}

/*************************************************************************
 *Clase se encarga de guardar un campo que toma los parametros del usuario
 *Para luego modificar un campo ya existente a partir de este
 *************************************************************************
 */
class ModifyFieldWindow : public QDialog
{
    Q_OBJECT
    
    //Metodos publicos
public:
    //Constructor y destructor
    explicit ModifyFieldWindow(QWidget *parent = 0);
    ~ModifyFieldWindow();

    //Mutadores y accesores
    Field* getField();
    int getIndex();
    void setFields(vector<Field*>);

    //Acciones que se pueden ejecutar
private slots:
    void on_MFWBt_Modify_clicked();

    //Caracteristicas privadas
private:
    Ui::ModifyFieldWindow *ui;
    Field* field;
    int index;
};

#endif // MODIFYFIELDWINDOW_H
