/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *NewFile;
    QAction *OpenFile;
    QAction *SaveFile;
    QAction *PrintFile;
    QAction *CloseFile;
    QAction *Exit;
    QAction *createField;
    QAction *modifyField;
    QAction *listField;
    QAction *insertRecord;
    QAction *searchRecord;
    QAction *deleteRecord;
    QAction *listRecord;
    QAction *crossTables;
    QAction *doSimpleIndexes;
    QAction *doBTree;
    QAction *reindex;
    QAction *exportXML;
    QAction *importXML;
    QAction *exportJSon;
    QAction *importJSon;
    QWidget *centralWidget;
    QTableView *MWTable;
    QMenuBar *menuBar;
    QMenu *menuArchivo;
    QMenu *menuCampos;
    QMenu *menuRegistros;
    QMenu *menuIndices;
    QMenu *menuUtilidades;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(632, 407);
        NewFile = new QAction(MainWindow);
        NewFile->setObjectName(QStringLiteral("NewFile"));
        OpenFile = new QAction(MainWindow);
        OpenFile->setObjectName(QStringLiteral("OpenFile"));
        SaveFile = new QAction(MainWindow);
        SaveFile->setObjectName(QStringLiteral("SaveFile"));
        PrintFile = new QAction(MainWindow);
        PrintFile->setObjectName(QStringLiteral("PrintFile"));
        CloseFile = new QAction(MainWindow);
        CloseFile->setObjectName(QStringLiteral("CloseFile"));
        Exit = new QAction(MainWindow);
        Exit->setObjectName(QStringLiteral("Exit"));
        createField = new QAction(MainWindow);
        createField->setObjectName(QStringLiteral("createField"));
        modifyField = new QAction(MainWindow);
        modifyField->setObjectName(QStringLiteral("modifyField"));
        listField = new QAction(MainWindow);
        listField->setObjectName(QStringLiteral("listField"));
        insertRecord = new QAction(MainWindow);
        insertRecord->setObjectName(QStringLiteral("insertRecord"));
        searchRecord = new QAction(MainWindow);
        searchRecord->setObjectName(QStringLiteral("searchRecord"));
        deleteRecord = new QAction(MainWindow);
        deleteRecord->setObjectName(QStringLiteral("deleteRecord"));
        listRecord = new QAction(MainWindow);
        listRecord->setObjectName(QStringLiteral("listRecord"));
        crossTables = new QAction(MainWindow);
        crossTables->setObjectName(QStringLiteral("crossTables"));
        doSimpleIndexes = new QAction(MainWindow);
        doSimpleIndexes->setObjectName(QStringLiteral("doSimpleIndexes"));
        doBTree = new QAction(MainWindow);
        doBTree->setObjectName(QStringLiteral("doBTree"));
        reindex = new QAction(MainWindow);
        reindex->setObjectName(QStringLiteral("reindex"));
        exportXML = new QAction(MainWindow);
        exportXML->setObjectName(QStringLiteral("exportXML"));
        importXML = new QAction(MainWindow);
        importXML->setObjectName(QStringLiteral("importXML"));
        exportJSon = new QAction(MainWindow);
        exportJSon->setObjectName(QStringLiteral("exportJSon"));
        importJSon = new QAction(MainWindow);
        importJSon->setObjectName(QStringLiteral("importJSon"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MWTable = new QTableView(centralWidget);
        MWTable->setObjectName(QStringLiteral("MWTable"));
        MWTable->setGeometry(QRect(20, 20, 591, 321));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 632, 20));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        menuCampos = new QMenu(menuBar);
        menuCampos->setObjectName(QStringLiteral("menuCampos"));
        menuRegistros = new QMenu(menuBar);
        menuRegistros->setObjectName(QStringLiteral("menuRegistros"));
        menuIndices = new QMenu(menuBar);
        menuIndices->setObjectName(QStringLiteral("menuIndices"));
        menuUtilidades = new QMenu(menuBar);
        menuUtilidades->setObjectName(QStringLiteral("menuUtilidades"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchivo->menuAction());
        menuBar->addAction(menuCampos->menuAction());
        menuBar->addAction(menuRegistros->menuAction());
        menuBar->addAction(menuIndices->menuAction());
        menuBar->addAction(menuUtilidades->menuAction());
        menuArchivo->addAction(NewFile);
        menuArchivo->addSeparator();
        menuArchivo->addAction(OpenFile);
        menuArchivo->addAction(SaveFile);
        menuArchivo->addSeparator();
        menuArchivo->addAction(PrintFile);
        menuArchivo->addSeparator();
        menuArchivo->addAction(CloseFile);
        menuArchivo->addAction(Exit);
        menuCampos->addAction(createField);
        menuCampos->addSeparator();
        menuCampos->addAction(modifyField);
        menuCampos->addSeparator();
        menuCampos->addAction(listField);
        menuRegistros->addAction(insertRecord);
        menuRegistros->addAction(searchRecord);
        menuRegistros->addAction(deleteRecord);
        menuRegistros->addAction(listRecord);
        menuRegistros->addSeparator();
        menuRegistros->addAction(crossTables);
        menuIndices->addAction(doSimpleIndexes);
        menuIndices->addSeparator();
        menuIndices->addAction(doBTree);
        menuIndices->addSeparator();
        menuIndices->addAction(reindex);
        menuUtilidades->addAction(exportXML);
        menuUtilidades->addAction(importXML);
        menuUtilidades->addSeparator();
        menuUtilidades->addAction(exportJSon);
        menuUtilidades->addAction(importJSon);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DataBase", 0));
        NewFile->setText(QApplication::translate("MainWindow", "Nuevo", 0));
        OpenFile->setText(QApplication::translate("MainWindow", "Abrir", 0));
        SaveFile->setText(QApplication::translate("MainWindow", "Salvar", 0));
        PrintFile->setText(QApplication::translate("MainWindow", "Imprimir", 0));
        CloseFile->setText(QApplication::translate("MainWindow", "Cerrar", 0));
        Exit->setText(QApplication::translate("MainWindow", "Salir", 0));
        createField->setText(QApplication::translate("MainWindow", "Crear", 0));
        modifyField->setText(QApplication::translate("MainWindow", "Modificar", 0));
        listField->setText(QApplication::translate("MainWindow", "Listar", 0));
        insertRecord->setText(QApplication::translate("MainWindow", "Insertar", 0));
        searchRecord->setText(QApplication::translate("MainWindow", "Buscar", 0));
        deleteRecord->setText(QApplication::translate("MainWindow", "Eliminar", 0));
        listRecord->setText(QApplication::translate("MainWindow", "Listar", 0));
        crossTables->setText(QApplication::translate("MainWindow", "Cruzar Tablas", 0));
        doSimpleIndexes->setText(QApplication::translate("MainWindow", "Crear Indices Simples", 0));
        doBTree->setText(QApplication::translate("MainWindow", "Crear Indices Arbol B", 0));
        reindex->setText(QApplication::translate("MainWindow", "Reindexar", 0));
        exportXML->setText(QApplication::translate("MainWindow", "Exportar XML", 0));
        importXML->setText(QApplication::translate("MainWindow", "Importar XML", 0));
        exportJSon->setText(QApplication::translate("MainWindow", "Exportar JSon", 0));
        importJSon->setText(QApplication::translate("MainWindow", "Importar JSon", 0));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
        menuCampos->setTitle(QApplication::translate("MainWindow", "Campos", 0));
        menuRegistros->setTitle(QApplication::translate("MainWindow", "Registros", 0));
        menuIndices->setTitle(QApplication::translate("MainWindow", "Indices", 0));
        menuUtilidades->setTitle(QApplication::translate("MainWindow", "Utilidades", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
