#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

private:
    ADTFile indicesFile;
    ADTFileRecord fileRecord;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
