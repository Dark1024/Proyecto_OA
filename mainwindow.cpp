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

        char* header = new char[ss.str().length() + 1];
        strcpy(header,ss.str().c_str());

        this->fileRecord.readHeader(header);

        int rl = 0;
        vector<Field*> fields = this->fileRecord.getFields();
        for(int i = 0; i < fields.size(); i++){
            rl += fields.at(i)->getLength();
        }
        this->fileRecord.setRecordLength(rl);

        //LEER EL ARCHIVO DE INDICES

        QString str = file.insert(file.size()-5,"-indices");

        if(this->indicesFile.open(str.toStdString(),ios_base::in | ios_base::out)){
            this->indicesFile.seekg(0,ios_base::end);
            streamoff indexLength = this->indicesFile.tellg();

            char* indexes = new char[indexLength+1];

            this->indicesFile.seekg(0,ios_base::beg);
            this->indicesFile.read(indexes,indexLength);

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
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cargar al archivo de indices");
            return;
        }

        if(this->fileRecord.isOpen()){
            QMessageBox::information(this,"Exitoso","Se han cargado los archivos correctamente");
        }else{
            QMessageBox::critical(this,"Error","Hubo un error al momento de cargar el archivo de registros");
        }
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al momento de abrir el archivo");
    }
}

void MainWindow::on_SaveFile_triggered()
{
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.flush() && this->indicesFile.flush()){
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
    this->indicesFile.close();
    if(this->fileRecord.isOpen()){
        if(this->fileRecord.close() && !this->indicesFile.isOpen()){
            while(this->fileRecord.fieldsSize() != 0){
                this->fileRecord.removeField(0);
            }
            this->fileRecord.cleanMap();
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

void MainWindow::on_createField_triggered()
{

    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","Ya no puede agregar un campo al archivo");
        return;
    }

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
        }

        string header = this->fileRecord.toStringHeader();
        cout<<header<<endl;
        this->fileRecord.setDataStart(header.size());
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        vector<Field*> fields = this->fileRecord.getFields();
        int rl = 0;
        for(int i = 0; i < fields.size(); i++){
            rl += fields.at(i)->getLength();
        }
        this->fileRecord.setRecordLength(rl);


        delete createField;
    }else{
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para crear un Campo");
    }
}

void MainWindow::on_modifyField_triggered()
{
    if(!this->fileRecord.indexesIsEmpty()){
        QMessageBox::critical(this,"Error","No puede modificar campos");
        return;
    }

    if(this->fileRecord.isOpen()){
        ModifyFieldWindow* modifyField = new ModifyFieldWindow();

        modifyField->setFields(this->fileRecord.getFields());
        modifyField->exec();

        Field* newField = modifyField->getField();

        if(newField != NULL){
            int index = modifyField->getIndex();
            this->fileRecord.modifyField(index,newField);
        }else{

        }

        string header = this->fileRecord.toStringHeader();
        this->fileRecord.seekp(0,ios_base::beg);
        this->fileRecord.write(header.c_str(),header.size());
        this->fileRecord.flush();

        delete modifyField;
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

void MainWindow::on_insertRecord_triggered()
{    
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

    if(record.size() != tmpfields.size()){
        QMessageBox::critical(this,"Error","Error en la cantidad de campos que lleno");
        return;
    }

    Record* newRecord =  new Record(tmpfields,record);

    if(this->fileRecord.addRecord(newRecord)){
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

        QMessageBox::information(this,"Correcto","Se ingreso correctamente el nuevo registro");
        delete newRecord;
    }else{
        QMessageBox::critical(this,"Error","Hubo un error al insertar el nuevo registro");
        delete newRecord;
    }
}

void MainWindow::on_searchRecord_triggered()
{
    vector<Field*> fields = this->fileRecord.getFields();
    QString str;

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

    PrimaryIndex* index = this->fileRecord.searchRecord(str.toStdString());

    if(index == NULL){
        QMessageBox::critical(this,"Error","El registro que buscaba no se encontro");
        return;
    }else{
        Record* record = this->fileRecord.getRecord(index);
        vector<string> r = record->getRecord();

        QStandardItemModel* model = new QStandardItemModel(1,1,this);
        for(int i = 0; i < fields.size(); i++){
            model->setHorizontalHeaderItem(i,new QStandardItem(QString::fromStdString(fields[i]->getName())));
        }

        for(int i = 0; i < fields.size(); i++){
            model->setItem(0,i,new QStandardItem(QString::fromStdString(r[i])));
        }
        delete record;
        ui->MWTable->setModel(model);
    }
}

void MainWindow::on_listRecord_triggered()
{
    QStandardItemModel* model = new QStandardItemModel(1,1,this);

    vector<Field*> fields = this->fileRecord.getFields();
    vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

    for(int i = 0; i < fields.size(); i++){
        model->setHorizontalHeaderItem(i,new QStandardItem(QString::fromStdString(fields[i]->getName())));
    }

    for(int i = 0; i < indexes.size(); i++){
        PrimaryIndex* currentIndex = indexes.at(i);
        if(currentIndex != NULL){
            Record* record = this->fileRecord.getRecord(currentIndex);
            vector<string> r = record->getRecord();

            for(int j = 0; j < fields.size(); j++){
                model->setItem(i,j,new QStandardItem(QString::fromStdString(r[j])));
            }
            delete record;
            ui->MWTable->setModel(model);
        }
    }
}

void MainWindow::on_deleteRecord_triggered()
{
    vector<Field*> fields = this->fileRecord.getFields();
    QString str;

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

    PrimaryIndex* index = this->fileRecord.searchRecord(str.toStdString());

    if(index == NULL){
        QMessageBox::critical(this,"Error","No se encontro el registro con la llave ingresada");
        return;
    }else{
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

void MainWindow::on_reindex_triggered()
{
    this->indicesFile.flush();
    this->indicesFile.close();
    this->fileRecord.cleanMap();

    if(this->indicesFile.open(this->indicesFile.getFileName(),ios_base::in | ios_base::out)){
        this->indicesFile.seekg(0,ios_base::end);
        streamoff indexLength = this->indicesFile.tellg();

        char* indexes = new char[indexLength+1];

        this->indicesFile.seekg(0,ios_base::beg);
        this->indicesFile.read(indexes,indexLength);

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

void MainWindow::on_doSimpleIndexes_triggered()
{
    this->indicesFile.flush();
    this->indicesFile.close();
    this->fileRecord.cleanMap();

    if(this->indicesFile.open(this->indicesFile.getFileName(),ios_base::in | ios_base::out)){
        this->indicesFile.seekg(0,ios_base::end);
        streamoff indexLength = this->indicesFile.tellg();

        char* indexes = new char[indexLength+1];

        this->indicesFile.seekg(0,ios_base::beg);
        this->indicesFile.read(indexes,indexLength);

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

void MainWindow::on_PrintFile_triggered()
{
    if(this->fileRecord.fieldsSize() == 0 || this->fileRecord.getIndexes().size() == 0){
        QMessageBox::warning(this,"Error","El archivo no contiene campos o registros");
        return;
    }

    QString path = QFileDialog::getExistingDirectory(this,"Imprimir archivo en PDF","");
    if(!path.isEmpty()){
        path += "/Registros.pdf";

        QString html = "";


        html += "<table border=\"1\">";

        vector<Field*> fields = this->fileRecord.getFields();

        html += "<tr>";
        for(int i = 0; i < fields.size(); i++){
            Field* currentField = fields.at(i);

            html += "<th>" + QString::fromStdString(currentField->getName()) + "</th>";
        }
        html += "</tr>";

        vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();


        for(int i = 0; i < indexes.size(); i++){
            PrimaryIndex* currentIndex = indexes.at(i);
            Record* currentRecord = this->fileRecord.getRecord(currentIndex);

            vector<string> currentVector = currentRecord->getRecord();

            html += "<tr>";
            for(int j = 0; j < currentVector.size(); j++){
                QString str = QString::fromStdString(currentVector[j]);
                str = str.trimmed();
                html += "<td>" + str + "</td>";
            }
            html += "</tr>";
        }

        html +="</table>";

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

void MainWindow::on_exportXML_triggered()
{
    if(!this->fileRecord.isOpen()){
        QMessageBox::critical(this,"Error","No tiene un archivo abierto para exportar sus campos y registros");
        return;
    }

    if(this->fileRecord.fieldsSize() == 0 || this->fileRecord.getIndexes().size() == 0){
        QMessageBox::warning(this,"Error","El archivo no tiene campos o registros");
        return;
    }

    QString path = QFileDialog::getExistingDirectory(this,"Exportar en archivo XML","");


    if(!path.isEmpty()){
        path += "/Registros.xml";

        QFile file (path);

        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"Error","No se puede exportar a xml, error al abrir archivo destino");
            return;
        }else{
            QXmlStreamWriter xmlw;
            xmlw.setDevice(&file);
            xmlw.writeStartDocument();

            xmlw.writeStartElement("fileRecord");

            vector<PrimaryIndex*> indexes = this->fileRecord.getIndexes();

            for(int i = 0; i < indexes.size(); i++){
                PrimaryIndex* currentIndex = indexes.at(i);

                Record* currentRecord = this->fileRecord.getRecord(currentIndex);
                vector<Field*> fields = currentRecord->getFields();
                vector<string> record = currentRecord->getRecord();

                xmlw.writeStartElement("record");

                for(int j = 0; j < fields.size(); j++){
                    Field* currentField = fields.at(j);

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
                xmlw.writeEndElement();
            }

            xmlw.writeEndElement();
            xmlw.writeEndDocument();

            QMessageBox::information(this,"Satisfactorio","Se ha creado correctamente el archivo XML");
        }
    }
}


void MainWindow::on_importXML_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,"Importar archivo XML","","XML (*.xml)");

    if(!file.isEmpty()){

        if(this->fileRecord.isOpen()){
            this->fileRecord.close();
        }
        if(this->indicesFile.isOpen()){
            this->indicesFile.close();
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

                        QDomDocument document;
                        QFile qfile(file);

                        if(!qfile.open(QIODevice::ReadOnly)){
                            QMessageBox::critical(this,"Error","Hubo un error en la lectura del archivo XML");
                            return;
                        }

                        if(!document.setContent(&qfile)){
                            QMessageBox::critical(this,"Error","Hubo un error de lectura del archivo XML");
                            return;
                        }

                        QDomElement db = document.documentElement();

                        QDomNode fr = db.firstChild().firstChild();

                        QDomElement elem = fr.toElement();

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

                                Field* newField = new Field(name.toStdString(),type,key,length,decimalPlaces);
                                this->fileRecord.addField(newField);
                                elem = elem.nextSibling().toElement();
                        }

                        int rl = 0;
                        vector<Field*> fields = this->fileRecord.getFields();
                        for(int i = 0; i < fields.size(); i++){
                            rl += fields.at(i)->getLength();
                        }
                        this->fileRecord.setRecordLength(rl);

                        this->fileRecord.cleanMap();

                        string header = this->fileRecord.toStringHeader();
                        this->fileRecord.write(header.c_str(),header.size());
                        this->fileRecord.flush();

                        QDomElement start_data = db.firstChild().toElement();

                        while(!start_data.isNull()){
                            vector<string> record;

                            QDomElement e = start_data.firstChild().toElement();
                            while(!e.isNull()){
                                record.push_back(e.text().trimmed().toStdString());
                                e = e.nextSibling().toElement();
                            }

                            Record* r  = new Record(this->fileRecord.getFields(),record);
                            this->fileRecord.addRecord(r);


                            start_data = start_data.nextSibling().toElement();
                        }

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
