/********************************************************************************
** Form generated from reading UI file 'newfieldwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFIELDWINDOW_H
#define UI_NEWFIELDWINDOW_H

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
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NewFieldWindow
{
public:
    QLineEdit *NFWLe_Name;
    QComboBox *NFWCB_Type;
    QSpinBox *NFWSp_Length;
    QSpinBox *NFWSp_Decimal;
    QCheckBox *NFWCB_Key;
    QPushButton *NFWBt_add;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *NewFieldWindow)
    {
        if (NewFieldWindow->objectName().isEmpty())
            NewFieldWindow->setObjectName(QStringLiteral("NewFieldWindow"));
        NewFieldWindow->resize(488, 291);
        NFWLe_Name = new QLineEdit(NewFieldWindow);
        NFWLe_Name->setObjectName(QStringLiteral("NFWLe_Name"));
        NFWLe_Name->setGeometry(QRect(210, 30, 251, 23));
        NFWCB_Type = new QComboBox(NewFieldWindow);
        NFWCB_Type->setObjectName(QStringLiteral("NFWCB_Type"));
        NFWCB_Type->setGeometry(QRect(210, 70, 151, 23));
        NFWSp_Length = new QSpinBox(NewFieldWindow);
        NFWSp_Length->setObjectName(QStringLiteral("NFWSp_Length"));
        NFWSp_Length->setGeometry(QRect(210, 110, 101, 24));
        NFWSp_Length->setMaximum(255);
        NFWSp_Decimal = new QSpinBox(NewFieldWindow);
        NFWSp_Decimal->setObjectName(QStringLiteral("NFWSp_Decimal"));
        NFWSp_Decimal->setGeometry(QRect(210, 150, 101, 24));
        NFWSp_Decimal->setMaximum(255);
        NFWCB_Key = new QCheckBox(NewFieldWindow);
        NFWCB_Key->setObjectName(QStringLiteral("NFWCB_Key"));
        NFWCB_Key->setGeometry(QRect(210, 190, 101, 21));
        NFWBt_add = new QPushButton(NewFieldWindow);
        NFWBt_add->setObjectName(QStringLiteral("NFWBt_add"));
        NFWBt_add->setGeometry(QRect(190, 240, 111, 31));
        label = new QLabel(NewFieldWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 131, 21));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(NewFieldWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 131, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(NewFieldWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(36, 110, 131, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(NewFieldWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(36, 150, 131, 21));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(NewFieldWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(36, 190, 131, 21));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(NewFieldWindow);

        QMetaObject::connectSlotsByName(NewFieldWindow);
    } // setupUi

    void retranslateUi(QDialog *NewFieldWindow)
    {
        NewFieldWindow->setWindowTitle(QApplication::translate("NewFieldWindow", "Nuevo Campo", 0));
        NFWCB_Type->clear();
        NFWCB_Type->insertItems(0, QStringList()
         << QApplication::translate("NewFieldWindow", "Cadena", 0)
         << QApplication::translate("NewFieldWindow", "Entero", 0)
         << QApplication::translate("NewFieldWindow", "Real", 0)
        );
        NFWCB_Key->setText(QApplication::translate("NewFieldWindow", "Activar", 0));
        NFWBt_add->setText(QApplication::translate("NewFieldWindow", "Agregar", 0));
        label->setText(QApplication::translate("NewFieldWindow", "Nombre:", 0));
        label_2->setText(QApplication::translate("NewFieldWindow", "Tipo:", 0));
        label_3->setText(QApplication::translate("NewFieldWindow", "Longitud:", 0));
        label_4->setText(QApplication::translate("NewFieldWindow", "Espacios Decimales:", 0));
        label_5->setText(QApplication::translate("NewFieldWindow", "Llave Primaria:", 0));
    } // retranslateUi

};

namespace Ui {
    class NewFieldWindow: public Ui_NewFieldWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFIELDWINDOW_H
