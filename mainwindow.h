#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Importacion de los encabezados necesarios para la ventana principal
#include "adtfilerecord.h"
#include "field.h"
#include "newfieldwindow.h"
#include "modifyfieldwindow.h"
#include "primaryindex.h"
#include "inputdialog.h"
#include "record.h"

#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QMap>
#include <QTextDocument>
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qprintdialog.h>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QXmlStreamWriter>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomAttr>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace Ui {
class MainWindow;
}

/****************************************************************
 *Esta clase es la encargada de manejar toda la ventana principal
 *Se encarga de ejecutar todo lo necesario para el funcionamiento
 *del programa
 ****************************************************************
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    //Metodos publicos de la clase principal
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Las acciones que se ejecutan con eventos
private slots:
    void on_NewFile_triggered();

    void on_SaveFile_triggered();

    void on_CloseFile_triggered();

    void on_Exit_triggered();

    void on_createField_triggered();

    void on_modifyField_triggered();

    void on_listField_triggered();

    void on_OpenFile_triggered();

    void on_insertRecord_triggered();

    void on_searchRecord_triggered();

    void on_listRecord_triggered();

    void on_deleteRecord_triggered();

    void on_reindex_triggered();

    void on_doSimpleIndexes_triggered();

    void on_PrintFile_triggered();

    void on_exportXML_triggered();

    void on_importXML_triggered();

    //Las pocas pero importantes propiedades de la clase principal
    void on_crossTables_triggered();

private:
    ADTFile indicesFile;
    ADTFileRecord fileRecord;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
