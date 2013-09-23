#include "inputdialog.h"
#include "ui_inputdialog.h"

//Constructor, inicializa los widgets de la ventana
InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

//Destructor, limpia la memoria y borra las ventanas
InputDialog::~InputDialog()
{
    delete ui;
}

//Se ejecuta cuando se click en el boton
void InputDialog::on_IDBotton_clicked()
{
    //Solamente guarda el texto que se escribe en el lineEdit
    if(ui->IDLineEdit->text().isEmpty()){
        QMessageBox::critical(this,"Error","No puede dejar el espacio vacio");
    }else{
        this->str = ui->IDLineEdit->text();
        this->close();
    }
}

//Retorna el texto que se guardo despues de la lectura
QString InputDialog::getString()
{
    return this->str;
}

//Metodo que hace las preparaciones necesarias al momento de mostrar la ventana al usuario
void InputDialog::setField(Field* field){
    //Cambia el texto que se muestra al usuario, ademas configura el tamnanio maximo que se puede ingresar
    ui->IDLabel->setText("Ingrese datos para el campo: " + QString::fromStdString(field->getName()));
    ui->IDLineEdit->setMaxLength(field->getLength());
    ui->IDLineEdit->setText("");

    //Utiliza expresiones regulares para validar el ingreso de texto
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

    //Configura el lineEdit para validar el texto que ingrese el usuario
    QRegExp exp(QString::fromStdString(ss.str()));
    ui->IDLineEdit->setValidator(new QRegExpValidator(exp,this));
}
