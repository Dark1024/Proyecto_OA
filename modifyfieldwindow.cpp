#include "modifyfieldwindow.h"
#include "ui_modifyfieldwindow.h"

ModifyFieldWindow::ModifyFieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyFieldWindow)
{
    ui->setupUi(this);
    this->field = NULL;
    QRegExp exp("[A-Za-z][A-Za-z0-9]*");
    ui->MFWLe_Nombre->setValidator(new QRegExpValidator(exp,this));
}

ModifyFieldWindow::~ModifyFieldWindow()
{
    delete ui;
}

void ModifyFieldWindow::on_MFWBt_Modify_clicked()
{
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

        this->field = new Field(name.toStdString(),'C',Key,0,0);
        this->close();
    }else{
        QMessageBox::warning(this,"Error","Ingrese el nuevo nombre del campo, no puede estar vacio");
    }
}

Field* ModifyFieldWindow::getField()
{
    return this->field;
}

int ModifyFieldWindow::getIndex()
{
    return this->index;
}

void ModifyFieldWindow::setFields(vector<Field*> fields)
{
    for(size_t i = 0; i < fields.size(); i++){
        ui->MFWCb_Fields->addItem(fields.at(i)->getName().c_str());
    }
}
