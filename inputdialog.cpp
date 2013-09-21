#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_IDBotton_clicked()
{
    if(ui->IDLineEdit->text().isEmpty()){
        QMessageBox::critical(this,"Error","No puede dejar el espacio vacio");
    }else{
        this->str = ui->IDLineEdit->text();
        this->close();
    }
}

QString InputDialog::getString()
{
    return this->str;
}

void InputDialog::setField(Field* field){
    ui->IDLabel->setText("Ingrese datos para el campo: " + QString::fromStdString(field->getName()));
    ui->IDLineEdit->setMaxLength(field->getLength());
    ui->IDLineEdit->setText("");

    stringstream ss;
    if(field->getType() == 'C'){
        ss<<"[A-Za-z][A-Za-z0-9]*";
    }else if(field->getType() == 'E'){
        ss<<"[0-9]*";
    }else{
        ss<<"[0-9]*\.[0-9]{1,"<<field->getDecimalPlaces()<<"}";
    }

    QRegExp exp(QString::fromStdString(ss.str()));
    ui->IDLineEdit->setValidator(new QRegExpValidator(exp,this));
}
