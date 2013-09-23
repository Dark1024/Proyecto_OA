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
    if(field->getType() == 'R'){
        ss<<"[0-9]*[.][0-9]{1,";
        ss<<field->getDecimalPlaces();
        ss<<"}";
    }else if(field->getType() == 'E'){
        ss<<"[0-9]*";
    }else{
        ss<<"[A-Za-z][A-Za-z0-9]*";
    }

    QRegExp exp(QString::fromStdString(ss.str()));
    ui->IDLineEdit->setValidator(new QRegExpValidator(exp,this));
}
