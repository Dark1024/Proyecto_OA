#include "newfieldwindow.h"
#include "ui_newfieldwindow.h"

//Constructor de la clase, ademas se valida la entrada de datos
NewFieldWindow::NewFieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFieldWindow)
{
    ui->setupUi(this);
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    ui->NFWLe_Name->setValidator(new QRegExpValidator(exp,this));
    this->field = NULL;
}

//Destructor de la clase
NewFieldWindow::~NewFieldWindow()
{
    delete ui;
}

//Se ejecuta al hacer click en el boton de crear
void NewFieldWindow::on_NFWBt_add_clicked()
{
    if(!ui->NFWLe_Name->text().isEmpty()){
        if(ui->NFWSp_Decimal->value() <= ui->NFWSp_Length->value()){
            QString name = ui->NFWLe_Name->text();

            int currentIndex = ui->NFWCB_Type->currentIndex();
            char Type;

            if(currentIndex == 2){
                Type = 'R';
            }else if(currentIndex == 1){
                Type = 'E';
            }else{
                Type = 'C';
            }

            int key;
            if(ui->NFWCB_Key->isChecked()){
                key = 1;
            }else{
                key = 0;
            }

            int length = ui->NFWSp_Length->value();
            int decimal = ui->NFWSp_Decimal->value();

            //Se crea el nuevo campo
            this->field = new Field(name.toStdString(),Type,key,length,decimal);
            cout<<this->field->toString()<<endl;

            this->close();
        }else{
            QMessageBox::critical(this,"Error","La cantidad de decimales no puede ser mayor que la longitud");
        }
    }else{
        QMessageBox::critical(this,"Error","Ingrese un texto para el nombre");
    }
}

//se retorna el campo almacenado adentro de la clase
Field* NewFieldWindow::getField()
{
    return this->field;
}
