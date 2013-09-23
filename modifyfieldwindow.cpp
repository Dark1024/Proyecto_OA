#include "modifyfieldwindow.h"
#include "ui_modifyfieldwindow.h"

//Constructor
ModifyFieldWindow::ModifyFieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyFieldWindow)
{
    ui->setupUi(this);
    this->field = NULL;
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    ui->MFWLe_Nombre->setValidator(new QRegExpValidator(exp,this));
}

//Destructor de la clase
ModifyFieldWindow::~ModifyFieldWindow()
{
    delete ui;
}

//se ejecuta al darle click al boton
void ModifyFieldWindow::on_MFWBt_Modify_clicked()
{
    //se encarga de crear un nuevo campo a partir de los datos obtenidos del usuario
    if(!ui->MFWLe_Nombre->text().isEmpty()){
        QString name = ui->MFWLe_Nombre->text();
        this->index = ui->MFWCb_Fields->currentIndex();
        bool val = ui->MFWCb_Key->isChecked();

        int Key;
        if(val){
            Key = 1;
        }else{
            Key =0;
        }

        //creacion del nuevo campo
        this->field = new Field(name.toStdString(),'C',Key,0,0);
        this->close();
    }else{
        QMessageBox::warning(this,"Error","Ingrese el nuevo nombre del campo, no puede estar vacio");
    }
}

//Se encarga de devolver el campo
Field* ModifyFieldWindow::getField()
{
    return this->field;
}

//se encarga de devolver el entero que dice cual es el campo que se modificara
int ModifyFieldWindow::getIndex()
{
    return this->index;
}

//se encarga de llenar el combobox para elegir el campo a modificar
void ModifyFieldWindow::setFields(vector<Field*> fields)
{
    for(size_t i = 0; i < fields.size(); i++){
        ui->MFWCb_Fields->addItem(fields.at(i)->getName().c_str());
    }
}
