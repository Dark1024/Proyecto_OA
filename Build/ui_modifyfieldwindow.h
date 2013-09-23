/********************************************************************************
** Form generated from reading UI file 'modifyfieldwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYFIELDWINDOW_H
#define UI_MODIFYFIELDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ModifyFieldWindow
{
public:
    QLineEdit *MFWLe_Nombre;
    QComboBox *MFWCb_Fields;
    QCheckBox *MFWCb_Key;
    QLabel *label;
    QLabel *label_2;
    QPushButton *MFWBt_Modify;
    QLabel *label_3;

    void setupUi(QDialog *ModifyFieldWindow)
    {
        if (ModifyFieldWindow->objectName().isEmpty())
            ModifyFieldWindow->setObjectName(QStringLiteral("ModifyFieldWindow"));
        ModifyFieldWindow->resize(492, 244);
        MFWLe_Nombre = new QLineEdit(ModifyFieldWindow);
        MFWLe_Nombre->setObjectName(QStringLiteral("MFWLe_Nombre"));
        MFWLe_Nombre->setGeometry(QRect(200, 40, 241, 23));
        MFWCb_Fields = new QComboBox(ModifyFieldWindow);
        MFWCb_Fields->setObjectName(QStringLiteral("MFWCb_Fields"));
        MFWCb_Fields->setGeometry(QRect(200, 90, 181, 23));
        MFWCb_Key = new QCheckBox(ModifyFieldWindow);
        MFWCb_Key->setObjectName(QStringLiteral("MFWCb_Key"));
        MFWCb_Key->setGeometry(QRect(200, 140, 91, 21));
        label = new QLabel(ModifyFieldWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 101, 21));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(ModifyFieldWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 90, 101, 20));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MFWBt_Modify = new QPushButton(ModifyFieldWindow);
        MFWBt_Modify->setObjectName(QStringLiteral("MFWBt_Modify"));
        MFWBt_Modify->setGeometry(QRect(190, 190, 111, 31));
        label_3 = new QLabel(ModifyFieldWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 140, 101, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(ModifyFieldWindow);

        QMetaObject::connectSlotsByName(ModifyFieldWindow);
    } // setupUi

    void retranslateUi(QDialog *ModifyFieldWindow)
    {
        ModifyFieldWindow->setWindowTitle(QApplication::translate("ModifyFieldWindow", "Modificar Campo", 0));
        MFWCb_Key->setText(QApplication::translate("ModifyFieldWindow", "Activar", 0));
        label->setText(QApplication::translate("ModifyFieldWindow", "Nuevo Nombre:", 0));
        label_2->setText(QApplication::translate("ModifyFieldWindow", "Campos:", 0));
        MFWBt_Modify->setText(QApplication::translate("ModifyFieldWindow", "Modificar", 0));
        label_3->setText(QApplication::translate("ModifyFieldWindow", "Llave Primaria:", 0));
    } // retranslateUi

};

namespace Ui {
    class ModifyFieldWindow: public Ui_ModifyFieldWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYFIELDWINDOW_H
