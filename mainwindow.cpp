#include "mainwindow.h"
#include "ui_mainwindow.h"

//Constructor de clase
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//Destructor de la clase
MainWindow::~MainWindow()
{
    delete ui;
}

//Encargado de crear un nuevo archivo
void MainWindow::on_NewFile_triggered()
{
    //Verifica si el archivo actual esta abierto
    if(this->fileRecord.isOpen()){
        this->fileRecord.close();
    }

    //Limpia el vector de campos y lo deja vacio
    while(this->fileRecord.fieldsSize() != 0){
        this->fileRecord.removeField(0);
    }

    //obtiene la direccion del archivo
    QString directory = QFileDialog::getExistingDirectory(this,"New File","");

    //verifica que no este vacio para continuar
    if(!directory.isEmpty()){
        bool val;
        //El usuario ingresa el nombre del nuevo archivo
        QString fileName = QInputDialog::getText(this,"Nombre del Archivo","Escriba el nombre del archivo que desea crear",QLineEdit::Normal,"",&val);

        //verifica que el usuario ingrese correctamente el nombre
        if(val && !fileName.isEmpty()){
            //Crea una direccion total para el nuevo archivo
            QString Path = directory + "/" + fileName + ".jjdb";

            //Abre el nuevo archivo con la direccion
            if(!this->fileRecord.open(Path.toStdString())){
                //Esta vez en modo de escritura
                this->fileRecord.open(Path.toStdString(),ios_base::out);

                //Escribe unos datos iniciales, los manda al archivo y lo cierra
                this->fileRecord.write("$$",2);
                this->fileRecord.flush();
                this->fileRecord.close();

                //Automaticamente se crea un archivo de indices a partir del archivo principal
                QString indicesPath = directory + "/" + fileName + "-indices.jjdb";

                //Se abre en modo de escritura, se escribe datos iniciales y se cierra
                this->indicesFile.open(indicesPath.toStdString().c_str(),ios_base::out);
                this->indicesFile.write("$$",2);
                this->indicesFile.flush();
                this->indicesFile.close();

                //vuelve a abrir el archivo pero esta vez en modo de lectura y escritura
                this->indicesFile.open(indicesPath.toStdString().c_str(),ios_base::in | ios_base::out);

                //hace lo mismo con el archivo principal
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

//Encargado de cargar el contenido de un archivo fisico ya existente
void MainWindow::on_OpenFile_triggered()
{
    //Verica que este abierto, si es asi entonces cierra el archivo
    if(this->fileRecord.isOpen()){
        this->fileRecord.flush();
        this->fileRecord.close();
    }

    //Obtiene la direccion del archivo que el usuario desea abrir
    QString file = QFileDialog::getOpenFileName(this,"Abrir Archivo","","Archivos de Base de datos(*.jjdb)");

    //Abre el archivo principal en modo de lectura y escritura
    if(this->fileRecord.open(file.toStdString(),ios_base::in | ios_base::out)){

        //Limpia el vector de campos, para que quede vacio
        while(this->fileRecord.fieldsSize() != 0){
            this->fileRecord.removeField(0);
        }

        //mueve el puntero de lectura al inicio
        this->fileRecord.seekg(1,ios_base::beg);

        //Lectura del header del archivo
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

        char* header = new char[ss.str().length() + 1];
        strcpy(header,ss.str().c_str());

        //Manda al metodo readHeader(char*) a que se encarge de cargar los campos
        this->fileRecord.readHeader(header);

        //Configura el tamanio de cada registro a partir de los campos creados
        int rl = 0;
        vector<Field*> fields = this->fileRecord.getFields();
        for(int i = 0; i < fields.size(); i++){
            rl += fields.at(i)->getLength();
        }
        this->fileRecord.setRecordLength(rl);

        //Inicia la lectura del archivo de indices para cargarlos

        //Modifica el nombre del archivo principal para cargar el de indices
        QString str = file.insert(file.size()-5,"-indices");

        //Abre el archivo de indices en modo de lectura y escritura
        if(this->indicesFile.open(str.toStdString(),ios_base::in | ios_base::out)){
            //mueve el puntero de lectura al final del archivo
            this->indicesFile.seekg(0,ios_base::end);

            //obtiene el tamanio del contenido leido para poder leerlo y cargarlo al programa
            streamoff indexLength = this->indicesFile.tellg();

            char* indexes = new char[indexLength+1];

            //Se hace la lectura del archivo
            this->indicesFile.seekg(0,ios_base::beg);
            this->indicesFile.read(indexes,indexLength);

            indexes[indexLength] = '\0';

            //Se transforma en un QString para la mejor manipulacion
            string str (indexes);
            QString qstr = QString::fromStdString(str);

            //hace una lista de cadenas despues de haberlas partido por ese caracter
            QStringList list = qstr.split("/");

            //itera la cantidad de indices primarios hayan en el archivo
            for(int i = 0; i < list.size(); i++){
                //vuelve a partir las cadenas para dejarlas de manera que se conviertan
                //en los atributos de los indices
                QStringList list2 = list.at(i).split(",");

                //se crean los atributos del indice primario
                string key = list2.at(0).toStdString();
                streamoff offset = atoll(list2.at(1).toStdString().c_str());

                //se crea el indice primario
                PrimaryIndex* newIndex = new PrimaryIndex(key,offset);
                this->fileRecord.insertIndex(key,newIndex);
            }
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cargar al archivo de indices");
            return;
        }

        //verifica si todo esta bien
        if(this->fileRecord.isOpen()){
            QMessageBox::information(this,"Exitoso","Se han cargado los archivos correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cargar el archivo de registros");
        }
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al momento de abrir el archivo");
    }
}

//Encargado de salvar todo el contenido que se ha escrito en los archivos
void MainWindow::on_SaveFile_triggered()
{
    //verifica si esta abierto el archivo
    if(this->fileRecord.isOpen()){
        //simplemente se hace un flush para mandarlos a guardar
        if(this->fileRecord.flush() && this->indicesFile.flush()){
            QMessageBox::information(this,"Correcto","El archivo se ha guardado correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de guardar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda salvar");
    }
}

//Encargado de cerrar los archivos utilizados
void MainWindow::on_CloseFile_triggered()
{
    //Cierra el archivo de indices
    this->indicesFile.close();
    if(this->fileRecord.isOpen()){
        //si esta abierto el archivo principal entonces se cierra
        if(this->fileRecord.close() && !this->indicesFile.isOpen()){

            //limpia el vector de campos del archivo
            while(this->fileRecord.fieldsSize() != 0){
                this->fileRecord.removeField(0);
            }

            //Limpia el mapa de indices primarios
            this->fileRecord.cleanMap();
            QMessageBox::information(this,"Correcto","El archivo se cerro correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cerrar el archivo");
        }
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto que pueda cerrar");
    }
}

//Encargado de cerrar la ventana principal y terminar la ejecucion del programa
void MainWindow::on_Exit_triggered()
{
    //Verifica si los archivos estan abiertos, se cierran y se limpia el mapa de indices primarios
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.close()){
            while(this->fileRecord.fieldsSize() != 0){
                this->fileRecord.removeField(0);
            }
            this->fileRecord.cleanMap();
            this->close();
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de guadar el archivo");
        }
    }else{
        this->close();
    }
}

//Encargado de crear un nuevo campo
void MainWindow::on_createField_triggered()
{
    //verifica que si hay registros dentro del archivo no cree ningun campo
    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","Ya no puede agregar un campo al archivo");
        return;
    }

    //verifica si el archivo esta abierto
    if(this->fileRecord.isOpen()){
        //crea una nueva ventana para pedir el nuevo campo
        NewFieldWindow* createField = new NewFieldWindow();

        //ejecuta la ventana
        createField->exec();

        //obtiene el nuevo campo que se ha creado
        Field* newField = createField->getField();

        //verifica que no sea nulo y verifica si este campo es la llave principal
        if(newField != NULL){
            for(int i = 0; i < this->fileRecord.fieldsSize(); i++){
                if(this->fileRecord.getField(i)->isKey()){
                    newField->setKey(0);
                    i = this->fileRecord.fieldsSize();
                }
            }
            //se agrega el nuevo campo al vector
            this->fileRecord.addField(newField);
        }

        //se manda a escribir los campos al archivo
        string header = this->fileRecord.toStringHeader();
        cout<<header<<endl;
        this->fileRecord.setDataStart(header.size());
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        //se obtiene el tamanio de cada registro del archivo
        vector<Field*> fields = this->fileRecord.getFields();
        int rl = 0;
        for(int i = 0; i < fields.size(); i++){
            rl += fields.at(i)->getLength();
        }
        this->fileRecord.setRecordLength(rl);

        //se elimina la ventana creada
        delete createField;
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para crear un Campo");
    }
}

//Encargada de modificar un campo ya existente
void MainWindow::on_modifyField_triggered()
{
    //verifica que si ya hay registros en el archivo no se pueda modificar ningun campo
    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","No puede modificar campos");
        return;
    }

    //verifica que archivo este abierto
    if(this->fileRecord.isOpen()){
        //crea una nueva ventana para pedir el campo que se desea modificar y por cual
        ModifyFieldWindow* modifyField = new ModifyFieldWindow();

        //se le manda el vector de campos para el combobox
        modifyField->setFields(this->fileRecord.getFields());
        modifyField->exec();

        //se toma el nuevo campo creado
        Field* newField = modifyField->getField();

        if(newField != NULL){
            //toma el indice para modificar ese campo
            int index = modifyField->getIndex();

            //modifica los atributos de un campo
            this->fileRecord.modifyField(index,newField);
        }else{

        }

        //escribe en el archivo el  nuevo header
        string header = this->fileRecord.toStringHeader();
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        delete modifyField;
    }else{
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para modificar sus campos");
    }
}

//Encargado de mostrar en la tabla principal todos los campos existentes
void MainWindow::on_listField_triggered()
{
    //verifica que el archivo este abierto
    if(!this->fileRecord.isOpen()){
        QMessageBox::warning(this,"Error","No tiene un archivo abierto para mostrar sus campos");
        return;
    }

    //verifica que existan campos en el vector de campos
    if(this->fileRecord.fieldsSize() <= 0){
        QMessageBox::warning(this,"Error","El archivo abierto no contiene campos");
        return;
    }

    //se crea un modelo para modificarlo y luego solo ponerselo a la tabla de la ventata principal
    QStandardItemModel* model = new QStandardItemModel(1,1,this);

    //se hacen los encabezados de la tabla
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Nombre")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("Tipo")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Llave")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QString("Longitud")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QString("Decimales")));

    //Se llenan las filas de tabla y se itera cuantas veces hayan campos para listarlos
    QString tmp;
    vector<Field*> fields = this->fileRecord.getFields();
    stringstream ss;

    for(int i = 0; i < fields.size(); i++){

        //columna de nombre
        tmp = QString::fromStdString(fields.at(i)->getName());
        model->setItem(i,0,new QStandardItem(tmp));

        //columna del tipo
        if(fields.at(i)->getType() == 'C'){
            model->setItem(i,1,new QStandardItem("Cadena"));
        }else if(fields.at(i)->getType() == 'E'){
            model->setItem(i,1,new QStandardItem("Entero"));
        }else{
            model->setItem(i,1,new QStandardItem("Real"));
        }

        //columna de la llave
        if(fields.at(i)->isKey()){
            model->setItem(i,2,new QStandardItem("Llave Primaria"));
        }else{
            model->setItem(i,2,new QStandardItem("No es Llave"));
        }

        //columna del tamanio
        ss<<fields.at(i)->getLength();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,3,new QStandardItem(tmp));

        //columna de los lugares decimales
        ss<< fields.at(i)->getDecimalPlaces();
        tmp = QString::fromStdString(ss.str());
        ss.str("");
        model->setItem(i,4,new QStandardItem(tmp));
    }
    //solo se le asigna el modelo a la tabla principal
    ui->MWTable->setModel(model);
}

//Encargado de insertar un nuevo registro al archivo
void MainWindow::on_insertRecord_triggered()
{    
    //verifica que existan campos en el archivo
    if(this->fileRecord.fieldsSize() == 0){
        QMessageBox::warning(this,"Error","No tiene campos en el archivo, por favor ingrese un campo para continuar");
        return;
    }

    //Validar que cuando se ingrese la llave, esta sea unica
    vector<string> record;
    vector<Field*> tmpfields = this->fileRecord.getFields();

    for(int i = 0; i < tmpfields.size(); i++){
        Field* currentField = tmpfields[i];

        InputDialog* idialog = new InputDialog();
        idialog->setField(currentField);
        idialog->exec();

        QString text = idialog->getString();

        record.push_back(text.toStdString());
        delete idialog;
    }

    //verifica que la cantidad de ingresos sea igual a la cantidad de campos
    if(record.size() != tmpfields.size()){
        QMessageBox::critical(this,"Error","Error en la cantidad de campos que lleno");
        return;
    }

    //crea un nuevo registro
    Record* newRecord =  new Record(tmpfields,record);

    //verficica que la llave primaria no exista
    if(this->fileRecord.addRecord(newRecord)){
        //Obtiene un vector de indices principales
        vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

        //genera como un toString para los indicies
        stringstream ss;
        for(int i = 0; i < indexes.size(); i++){
            ss<<indexes.at(i)->toString();
            if(i != indexes.size() -1){
                ss<<'/';
            }
        }

        //guarda los indices primarios en el archivo
        this->indicesFile.seekp(0,ios_base::beg);
        this->indicesFile.write(ss.str().c_str(),ss.str().length());
        this->indicesFile.flush();

        QMessageBox::information(this,"Correcto","Se ingreso correctamente el nuevo registro");
        delete newRecord;
        //lo borra de memoria, pero ya esta guardado en el archivo
    }else{
        //borra el nuevo registro porque no sirvio de nada
        QMessageBox::critical(this,"Error","Hubo un error al insertar el nuevo registro");
        delete newRecord;
    }
}


//Encargado de buscar un registro y mostrarlo
void MainWindow::on_searchRecord_triggered()
{
    //toma el vector de campos
    vector<Field*> fields = this->fileRecord.getFields();
    QString str;

    //muestra una ventana para que se busque el registro a partir de su clave
    for(int i = 0; i< fields.size(); i++){
        Field* currentField = fields.at(i);
        if(currentField->isKey()){
            InputDialog* idialog = new InputDialog();
            idialog->setField(currentField);
            idialog->exec();

            if(idialog->getString().isEmpty()){
                return;
            }

            str = idialog->getString();
            delete idialog;
       }
    }

    //Obtiene un indice primario de la busqueda en el mapa de indices primarios
    PrimaryIndex* index = this->fileRecord.searchRecord(str.toStdString());

    //En caso de que no se encuentre el registro, este indice primario es nulo
    if(index == NULL){
        QMessageBox::critical(this,"Error","El registro que buscaba no se encontro");
        return;
    }else{
        //se obtiene un registro a partir del indice primario
        Record* record = this->fileRecord.getRecord(index);
        vector<string> r = record->getRecord();

        //se hace el modelo para poder mostrar el registro
        QStandardItemModel* model = new QStandardItemModel(1,1,this);

        //se hacen los encabezados de la tabla
        for(int i = 0; i < fields.size(); i++){
            model->setHorizontalHeaderItem(i,new QStandardItem(QString::fromStdString(fields[i]->getName())));
        }

        //se la fila para el registro
        for(int i = 0; i < fields.size(); i++){
            model->setItem(0,i,new QStandardItem(QString::fromStdString(r[i])));
        }

        //se elimina el registro de memoria porque esta guardado en el archivo
        delete record;

        //se asigna el modelo a la tabla del main
        ui->MWTable->setModel(model);
    }
}

//Encargado de mostrar todos los registros que existen en el archivo
void MainWindow::on_listRecord_triggered()
{
    //se hace el modelo de la tabla
    QStandardItemModel* model = new QStandardItemModel(1,1,this);

    //se toman los vectores de campos y el otro de los indices primarios
    vector<Field*> fields = this->fileRecord.getFields();
    vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

    //se inserta el encabezado de la tabla
    for(int i = 0; i < fields.size(); i++){
        model->setHorizontalHeaderItem(i,new QStandardItem(QString::fromStdString(fields[i]->getName())));
    }

    //Busca el registro en el archivo y de una vez lo asigna al modelo
    for(int i = 0; i < indexes.size(); i++){
        PrimaryIndex* currentIndex = indexes.at(i);
        if(currentIndex != NULL){
            Record* record = this->fileRecord.getRecord(currentIndex);
            vector<string> r = record->getRecord();

            for(int j = 0; j < fields.size(); j++){
                model->setItem(i,j,new QStandardItem(QString::fromStdString(r[j])));
            }
            //borra el registro de la memoria
            delete record;
        }
    }
    //asigna el modelo
    ui->MWTable->setModel(model);
}

//se encarga de eliminar un registro, solamente lo marca y lo elimina de los indices primarios
//para que despues se le pase el compactar
void MainWindow::on_deleteRecord_triggered()
{
    vector<Field*> fields = this->fileRecord.getFields();
    QString str;

    for(int i = 0; i< fields.size(); i++){
        Field* currentField = fields.at(i);
        if(currentField->isKey()){
            //se le muestra una nueva ventana para pedir la llave primaria
            InputDialog* idialog = new InputDialog();
            idialog->setField(currentField);
            idialog->exec();

            if(idialog->getString().isEmpty()){
                return;
            }

            str = idialog->getString();
            delete idialog;
       }
    }

    //toma el indice primario por medio de una busqueda
    PrimaryIndex* index = this->fileRecord.searchRecord(str.toStdString());

    if(index == NULL){
        QMessageBox::critical(this,"Error","No se encontro el registro con la llave ingresada");
        return;
    }else{
        //se borra el registro de los indices primarios y se marca con un * en el archivo de registros
        if(this->fileRecord.deleteRecord(index)){
            vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

            stringstream ss;
            for(int i = 0; i < indexes.size(); i++){
                ss<<indexes.at(i)->toString();
                if(i != indexes.size() -1){
                    ss<<'/';
                }
            }
            this->indicesFile.seekp(0,ios_base::beg);
            this->indicesFile.write(ss.str().c_str(),ss.str().length());
            this->indicesFile.flush();

            QMessageBox::information(this,"Correcto","Se ha podido eliminar el registro correctamente");
        }else{
            QMessageBox::critical(this,"Error","No se pudo eliminar el registro, no se encuentra la llave");
        }
    }
}

//Reindexar se encargar de volver a crear los indices primarios a partir del archivo de indices
void MainWindow::on_reindex_triggered()
{
    //Primero lo cierra y limpia el mapa de indices primarios
    this->indicesFile.flush();
    this->indicesFile.close();
    this->fileRecord.cleanMap();

    //lo vuelve a abrir en modo de lectura y escritura
    if(this->indicesFile.open(this->indicesFile.getFileName(),ios_base::in | ios_base::out)){
        //se mueve al final para obtener el tamanio del contenido del archivo
        this->indicesFile.seekg(0,ios_base::end);
        streamoff indexLength = this->indicesFile.tellg();

        char* indexes = new char[indexLength+1];

        //mueve el puntero al inicio y hace la lectura del archivo
        this->indicesFile.seekg(0,ios_base::beg);
        this->indicesFile.read(indexes,indexLength);

        //hace lo necesario para crear los indices primarios
        indexes[indexLength] = '\0';
        string str (indexes);
        QString qstr = QString::fromStdString(str);

        QStringList list = qstr.split("/");

        for(int i = 0; i < list.size(); i++){
            QStringList list2 = list.at(i).split(",");

            string key = list2.at(0).toStdString();
            streamoff offset = atoll(list2.at(1).toStdString().c_str());

            PrimaryIndex* newIndex = new PrimaryIndex(key,offset);
            this->fileRecord.insertIndex(key,newIndex);
        }
        QMessageBox::information(this,"Satisfactorio","Se ha reindexado correctamente");
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al momento de cargar al archivo de indices");
        return;
    }
}

//Este metodo es el encargado crear los indices primarios
void MainWindow::on_doSimpleIndexes_triggered()
{
    //si el archivo esta abiero lo cierra
    this->indicesFile.flush();
    this->indicesFile.close();
    this->fileRecord.cleanMap();

    //se vuelve a abrir el archivo de indices en modo de lectura y escritura
    if(this->indicesFile.open(this->indicesFile.getFileName(),ios_base::in | ios_base::out)){
        this->indicesFile.seekg(0,ios_base::end);
        streamoff indexLength = this->indicesFile.tellg();

        char* indexes = new char[indexLength+1];

        //se hace la lectura del archivo
        this->indicesFile.seekg(0,ios_base::beg);
        this->indicesFile.read(indexes,indexLength);

        //Lo que se necesita para crear los indices
        indexes[indexLength] = '\0';
        string str (indexes);
        QString qstr = QString::fromStdString(str);

        QStringList list = qstr.split("/");

        for(int i = 0; i < list.size(); i++){
            QStringList list2 = list.at(i).split(",");

            string key = list2.at(0).toStdString();
            streamoff offset = atoll(list2.at(1).toStdString().c_str());

            PrimaryIndex* newIndex = new PrimaryIndex(key,offset);
            this->fileRecord.insertIndex(key,newIndex);
        }
        QMessageBox::information(this,"Satisfactorio","Se han creado los indices simples");
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al momento de cargar al archivo de indices");
        return;
    }
}

//Se encarga de exportar los registros del archivo principal a un archivo de tipo PDF
void MainWindow::on_PrintFile_triggered()
{
    //verifica que se encuentren campos y registros dentro del archivo
    if(this->fileRecord.fieldsSize() == 0 || this->fileRecord.getIndexes().size() == 0){
        QMessageBox::warning(this,"Error","El archivo no contiene campos o registros");
        return;
    }

    //Toma la direccion donde ira a poner el archivo PDF
    QString path = QFileDialog::getExistingDirectory(this,"Imprimir archivo en PDF","");
    if(!path.isEmpty()){
        path += "/Registros.pdf";

        //crea un codigo HTML donde se iran todas las instrucciones para la creacion de una tabla
        //que contenga todos los registros.
        QString html = "";

        //se insertan las tags del las caracteristicas de la tabla
        html += "<table border=\"1\">";

        vector<Field*> fields = this->fileRecord.getFields();

        //crea un tag para hacer una fila en la tabla
        html += "<tr>";

        //le inserta el nombre de cada uno de los campos la tabla
        for(int i = 0; i < fields.size(); i++){
            //Los anade en el header de la tabla
            Field* currentField = fields.at(i);

            html += "<th>" + QString::fromStdString(currentField->getName()) + "</th>";
        }
        html += "</tr>";

        //obtiene los indices primarios
        vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

        //inserta los registros a la tabla
        for(int i = 0; i < indexes.size(); i++){
            PrimaryIndex* currentIndex = indexes.at(i);
            Record* currentRecord = this->fileRecord.getRecord(currentIndex);

            vector<string> currentVector = currentRecord->getRecord();

            //inserta al codigo html los registros
            html += "<tr>";
            for(int j = 0; j < currentVector.size(); j++){
                QString str = QString::fromStdString(currentVector[j]);
                str = str.trimmed();
                html += "<td>" + str + "</td>";
            }
            html += "</tr>";
        }

        html +="</table>";

        //Ahora se hace del uso de un QPrinter para poder generar el archivo pdf
        QTextDocument document;
        document.setHtml(html);
        QPrinter printer;
        printer.setOutputFileName(path);
        printer.setOutputFormat(QPrinter::PdfFormat);
        document.print(&printer);
        printer.newPage();

        QMessageBox::information(this,"Satisfactorio","Los registros se han impreso en el archivo Registro.pdf");
    }
}

//Encargado de mostrar los registros del archivo en una estructura de xml
void MainWindow::on_exportXML_triggered()
{
    //verifica que el archivo este abierto
    if(!this->fileRecord.isOpen()){
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para exportar sus campos y registros");
        return;
    }

    //verifica que existan campos y registros
    if(this->fileRecord.fieldsSize() == 0 || this->fileRecord.getIndexes().size() == 0){
        QMessageBox::warning(this,"Error","El archivo no tiene campos o registros");
        return;
    }

    //Obtiene del usuario la direccion del archivo donde se guardara el xml
    QString path = QFileDialog::getExistingDirectory(this,"Exportar en archivo XML","");

    //verifica que esa direccion sea correcta
    if(!path.isEmpty()){
        path += "/Registros.xml";

        //Utiliza un Qfile para poder hacer la escritura correcta del codigo xml
        QFile file (path);

        //verifica que este abierto en modo de escritura solamente
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"Error","No se puede exportar a xml, error al abrir archivo destino");
            return;
        }else{
            //se hace del uso de un QXmlStreamWriter que ayuda a escribir el codigo XML dentro del archivo
            QXmlStreamWriter xmlw;
            xmlw.setDevice(&file);
            //se escribe el principio del documento
            xmlw.writeStartDocument();

            //se escribe el encabezado del archivo de xml
            xmlw.writeStartElement("fileRecord");

            vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

            //se escriben los subarboles del principal, es uno por cada registro
            for(int i = 0; i < indexes.size(); i++){
                PrimaryIndex* currentIndex = indexes.at(i);

                Record* currentRecord = this->fileRecord.getRecord(currentIndex);
                vector<Field*> fields = currentRecord->getFields();
                vector<string> record = currentRecord->getRecord();

                xmlw.writeStartElement("record");

                //adentro de cada uno de los subarboles se crean otros subarboles, uno por cada campo con
                //su registro que le corresponde
                for(int j = 0; j < fields.size(); j++){
                    Field* currentField = fields.at(j);

                    //se escribe los registros junto con sus campos
                    xmlw.writeStartElement(QString::fromStdString(currentField->getName()));
                    if(currentField->isKey()){
                        xmlw.writeAttribute("key","true");
                    }else{
                        xmlw.writeAttribute("key","false");
                    }

                    if(currentField->getType() == 'E'){
                        xmlw.writeAttribute("type","integer");
                    }else if(currentField->getType() == 'R'){
                        xmlw.writeAttribute("type","real");
                    }else{
                        xmlw.writeAttribute("type","string");
                    }

                    xmlw.writeAttribute("length",QString::number(currentField->getLength()));

                    if(currentField->getType() == 'R'){
                        xmlw.writeAttribute("decimalPlaces",QString::number(currentField->getDecimalPlaces()));
                    }

                    QString str = QString::fromStdString(record[j]).trimmed();
                    xmlw.writeCharacters(str);
                    xmlw.writeEndElement();
                }
                //se escribe el final del elemento
                xmlw.writeEndElement();
            }

            //se escribe el final del elemento
            xmlw.writeEndElement();
            //se escribe el final del documento
            xmlw.writeEndDocument();

            QMessageBox::information(this,"Satisfactorio","Se ha creado correctamente el archivo XML");
        }
    }
}

//Encargado de generar un nuevo archivo de registros a partir de un archivo XML
void MainWindow::on_importXML_triggered()
{
    //Se obtiene la direccion del archivo xml
    QString file = QFileDialog::getOpenFileName(this,"Importar archivo XML","","XML (*.xml)");

    //verifica que la direccion este bien
    if(!file.isEmpty()){

        //si esta abierto un archivo de registros entonces lo cierra y muestra al usuario
        //a que escoga el lugar de destino del nuevo archivo que se escribe

        //verifica que los archivos este cerrados
        if(this->fileRecord.isOpen()){
            this->fileRecord.close();
        }
        if(this->indicesFile.isOpen()){
            this->indicesFile.close();
        }

        //Limpia el vector de campos del archivo
        while(this->fileRecord.fieldsSize() != 0){
            this->fileRecord.removeField(0);
        }

        //toma la direccion del nuevo archivo de registros
        QString directory = QFileDialog::getExistingDirectory(this,"New File","");
        if(!directory.isEmpty()){
            bool val;
            //Pregunta el nombre del archivo destino
            QString fileName = QInputDialog::getText(this,"Nombre del Archivo","Escriba el nombre del archivo que desea crear",QLineEdit::Normal,"",&val);
            if(val && !fileName.isEmpty()){
                QString Path = directory + "/" + fileName + ".jjdb";
                //escribe algo, luego lo cierra y vuelve a abrir
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

                        //se hace del uso de un QDomDocument que permite la lectura del xml
                        QDomDocument document;

                        //uso de un qfile
                        QFile qfile(file);

                        //verifica que archivo este abierto solamente en modo de lectura
                        if(!qfile.open(QIODevice::ReadOnly)){
                            QMessageBox::critical(this,"Error","Hubo un error en la lectura del archivo XML");
                            return;
                        }

                        //le asigna el contenido del archivo al documento que permite la lectura
                        if(!document.setContent(&qfile)){
                            QMessageBox::critical(this,"Error","Hubo un error de lectura del archivo XML");
                            return;
                        }

                        //Esta lectura se basa especificamente en tomar los elementos y crear registros
                        //a partir de ellos
                        QDomElement db = document.documentElement();

                        QDomNode fr = db.firstChild().firstChild();

                        QDomElement elem = fr.toElement();

                        //verifica que los elementos no sean nulos
                        while(!elem.isNull()){
                                QString name = elem.tagName();

                                if(!elem.hasAttributes()){
                                    QMessageBox::critical(this,"Error","El archivo XML contiene una mala estructura");
                                    return;
                                }

                                QDomNamedNodeMap map = elem.attributes();

                                char type;
                                int length;
                                int decimalPlaces = 0;
                                int key = 0;

                                if(map.size() < 3){
                                    QMessageBox::critical(this,"Error","El archivo XML contiene una mala estructura");
                                    return;
                                }

                                //toma de los elementos xml y los convierte a las caracteristicas de un registro
                                for(int i = 0; i < map.size(); i++){
                                    if(!map.item(i).isNull()){
                                        QDomNode node = map.item(i);
                                        QDomAttr attr = node.toAttr();

                                        if(attr.name() == "key"){
                                            if(attr.value() == "true"){
                                                key = 1;
                                            }
                                        }else if(attr.name() == "type"){
                                            if(attr.value() == "integer"){
                                                type = 'E';
                                            }else if(attr.value() == "real"){
                                                type = 'R';
                                            }else{
                                                type = 'C';
                                            }
                                        }else if(attr.name() == "length"){
                                            length = attr.value().toInt();
                                        }else if(attr.name() == "decimalPlaces"){
                                            decimalPlaces = attr.value().toInt();
                                        }else{
                                            QMessageBox::critical(this,"Error","El archivo XML tiene una mala estructura");
                                            return;
                                        }
                                    }else{
                                        QMessageBox::critical(this,"Error","Mala estructura del archivo XML");
                                        return;
                                    }
                                }

                                //creacion de un nuevo registro
                                Field* newField = new Field(name.toStdString(),type,key,length,decimalPlaces);
                                this->fileRecord.addField(newField);
                                elem = elem.nextSibling().toElement();
                        }

                        //cambia el tamanio de los registros del archivo
                        int rl = 0;
                        vector<Field*> fields = this->fileRecord.getFields();
                        for(int i = 0; i < fields.size(); i++){
                            rl += fields.at(i)->getLength();
                        }
                        this->fileRecord.setRecordLength(rl);

                        //limpia el mapa de indices primarios
                        this->fileRecord.cleanMap();

                        //se encarga de hacer el header del archivo y guardar los campos
                        string header = this->fileRecord.toStringHeader();
                        this->fileRecord.write(header.c_str(),header.size());
                        this->fileRecord.flush();

                        QDomElement start_data = db.firstChild().toElement();

                        //se encarga especificamente de tomar los datos del xml
                        //y los convierte en los registros
                        while(!start_data.isNull()){
                            vector<string> record;

                            QDomElement e = start_data.firstChild().toElement();
                            while(!e.isNull()){
                                record.push_back(e.text().trimmed().toStdString());
                                e = e.nextSibling().toElement();
                            }

                            //creacion de un nuevo registro
                            Record* r  = new Record(this->fileRecord.getFields(),record);
                            this->fileRecord.addRecord(r);


                            start_data = start_data.nextSibling().toElement();
                        }

                        //ahora se encarga de hacer los indices y de guardarlos en el archivo de indices
                        vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

                        stringstream ss;
                        for(int i = 0; i < indexes.size(); i++){
                            ss<<indexes.at(i)->toString();
                            if(i != indexes.size() -1){
                                ss<<'/';
                            }
                        }
                        this->indicesFile.seekp(0,ios_base::beg);
                        this->indicesFile.write(ss.str().c_str(),ss.str().length());
                        this->indicesFile.flush();

                        //solamente cierra el archivo xml
                        qfile.close();

                        QMessageBox::information(this,"Satisfactorio","Se ha creado el archivo de registros correctamente");

                    }else{
                        QMessageBox::critical(this,"Error","Hubo un error inesperado al momento de abrir el archivo creado");
                    }
                }else{
                    QMessageBox::critical(this,"Error","Hubo un error al momento de abrir el archivo para su inicializacion");
                }
            }
        }

    }
}

void MainWindow::on_crossTables_triggered()
{
    return;//xD

    //verifica si el archivo de registros esta abierto
    if(!this->fileRecord.isOpen()){
        QMessageBox::warning(this,"Error","No contiene un archivo de registros abierto");
        return;
    }

    ADTFile* empl;

    QString file = QFileDialog::getOpenFileName(this,"Abrir archivo .csv","","Archivos CSV(*.csv)");

    if(empl->open(file.toStdString(),ios_base::in)){
        empl->seekg(0,ios_base::beg);
        //NO SE QUE HACER XD
    }
}
