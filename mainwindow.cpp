#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewFile_triggered()
{
    if(this->fileRecord.isOpen()){
        this->fileRecord.close();
    }

    while(this->fileRecord.fieldsSize() != 0){
        this->fileRecord.removeField(0);
    }

    QString directory = QFileDialog::getExistingDirectory(this,"New File","");
    if(!directory.isEmpty()){
        bool val;
        QString fileName = QInputDialog::getText(this,"Nombre del Archivo","Escriba el nombre del archivo que desea crear",QLineEdit::Normal,"",&val);
        if(val && !fileName.isEmpty()){
            QString Path = directory + "/" + fileName + ".jjdb";
            if(!this->fileRecord.open(Path.toStdString())){
                this->fileRecord.open(Path.toStdString(),ios_base::out);
                this->fileRecord.write("$$",2);
                this->fileRecord.flush();
                this->fileRecord.close();

                QString indicesPath = directory + "/" + fileName + "-indices.jjdb";
                this->indicesFile.open(indicesPath.toStdString().c_str(),ios_base::out);
                this->indicesFile.write("$$",2);
                this->indicesFile.flush();
                this->indicesFile.close();

                this->indicesFile.open(indicesPath.toStdString().c_str(),ios_base::in | ios_base::out);

                if(this->fileRecord.open(Path.toStdString(),ios_base::in | ios_base::out)){
                    QMessageBox::information(this,"Correcto","Se creo y se abrio el archivo correctamente");
                }else{
                    QMessageBox::critical(this,"Error","Hubo un error inesperado al momento de abrir el archivo creado");
                }
            }else{
                QMessageBox::critical(this,"Error","Hubo un error al momento de abrir el archivo para su inicializacion");
            }
        }
    }
}

void MainWindow::on_OpenFile_triggered()
{
    if(this->fileRecord.isOpen()){
        this->fileRecord.flush();
        this->fileRecord.close();
    }

    QString file = QFileDialog::getOpenFileName(this,"Abrir Archivo","","Archivos de Base de datos(*.jjdb)");

    if(this->fileRecord.open(file.toStdString(),ios_base::in | ios_base::out)){
        while(this->fileRecord.fieldsSize() != 0){
            this->fileRecord.removeField(0);
        }

        this->fileRecord.seekg(1,ios_base::beg);

        char* tmp = new char[2];
        stringstream ss;
        int data_start = 0;

        while(this->fileRecord.read(tmp,1) != NULL){
            data_start++;
            if(tmp[0] == '$' && data_start != 1){
                break;
            }else{
                ss<<tmp[0];
            }
        }
        data_start++;
        this->fileRecord.setDataStart(data_start);
        cout<<"Data Start: "<<this->fileRecord.getDataStart()<<endl;

        char* header = new char[ss.str().length() + 1];
        strcpy(header,ss.str().c_str());

        this->fileRecord.readHeader(header);

        if(this->fileRecord.isOpen()){
            QMessageBox::information(this,"Exitoso","Se ha cargado el encabezado del archivo correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cargar el encabezado del archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al momento de abrir el archivo");
    }
}

void MainWindow::on_SaveFile_triggered()
{
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.flush()){
            QMessageBox::information(this,"Correcto","El archivo se ha guardado correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de guardar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda salvar");
    }
}


void MainWindow::on_CloseFile_triggered()
{
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.close()){
            QMessageBox::information(this,"Correcto","El archivo se cerro correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cerrar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda cerrar");
    }
}

void MainWindow::on_Exit_triggered()
{
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.close()){
            this->close();
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de guadar el archivo");
        }
    }else{
        this->close();
    }
}

void MainWindow::on_createField_triggered()
{
    //FALTA VALIDAR QUE NO SE AGREGREN CAMPOS SI HAY REGISTROS
    if(this->fileRecord.isOpen()){
        NewFieldWindow* createField = new NewFieldWindow();
        createField->exec();

        Field* newField = createField->getField();
        if(newField != NULL){
            for(int i = 0; i < this->fileRecord.fieldsSize(); i++){
                if(this->fileRecord.getField(i)->isKey()){
                    newField->setKey(0);
                    i = this->fileRecord.fieldsSize();
                }
            }
            this->fileRecord.addField(newField);
        }else{
            cout<<"Campo NULL"<<endl;
        }

        string header = this->fileRecord.toStringHeader();
        cout<<header<<endl;
        this->fileRecord.setDataStart(header.size());
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        delete createField;
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para crear un Campo");
    }
}

void MainWindow::on_modifyField_triggered()
{
    if(this->fileRecord.isOpen()){
        ModifyFieldWindow* modifyField = new ModifyFieldWindow();
        cout<<"Marca1"<<endl;
        modifyField->setFields(this->fileRecord.getFields());
        modifyField->exec();

        cout<<"Marca2"<<endl;
        Field* newField = modifyField->getField();

        if(newField != NULL){
            int index = modifyField->getIndex();
            this->fileRecord.modifyField(index,newField);
        }else{
            cout<<"Campo NULL"<<endl;
        }

        string header = this->fileRecord.toStringHeader();
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        delete modifyField;

        //FALTA CORRER LOS REGISTROS DESPUES DE MODIFICAR EL CAMPO
    }else{
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para modificar sus campos");
    }
}


void MainWindow::on_listField_triggered()
{
    if(!this->fileRecord.isOpen()){
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para mostrar sus campos");
        return;
    }

    if(this->fileRecord.fieldsSize() <= 0){
        QMessageBox::warning(this,"Error","El archivo abierto no contiene campos");
        return;
    }

    QStandardItemModel* model = new QStandardItemModel(1,1,this);

    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Nombre")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("Tipo")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Llave")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QString("Longitud")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QString("Decimales")));

    QString tmp;
    vector<Field*> fields = this->fileRecord.getFields();
    stringstream ss;

    for(int i = 0; i < fields.size(); i++){

        tmp = QString::fromStdString(fields.at(i)->getName());
        model->setItem(i,0,new QStandardItem(tmp));

        if(fields.at(i)->getType() == 'C'){
            model->setItem(i,1,new QStandardItem("Cadena"));
        }else if(fields.at(i)->getType() == 'E'){
            model->setItem(i,1,new QStandardItem("Entero"));
        }else{
            model->setItem(i,1,new QStandardItem("Real"));
        }

        if(fields.at(i)->isKey()){
            model->setItem(i,2,new QStandardItem("Llave Primaria"));
        }else{
            model->setItem(i,2,new QStandardItem("No es Llave"));
        }

        ss<<fields.at(i)->getLength();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,3,new QStandardItem(tmp));

        ss<< fields.at(i)->getDecimalPlaces();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,4,new QStandardItem(tmp));
    }
    ui->MWTable->setModel(model);
}
