/********************************************************************************
** Form generated from reading UI file 'dialog_connect.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CONNECT_H
#define UI_DIALOG_CONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog_connect
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QDialog *dialog_connect)
    {
        if (dialog_connect->objectName().isEmpty())
            dialog_connect->setObjectName(QString::fromUtf8("dialog_connect"));
        dialog_connect->resize(270, 72);
        widget = new QWidget(dialog_connect);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 248, 53));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 1, 2, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);


        retranslateUi(dialog_connect);

        QMetaObject::connectSlotsByName(dialog_connect);
    } // setupUi

    void retranslateUi(QDialog *dialog_connect)
    {
        dialog_connect->setWindowTitle(QCoreApplication::translate("dialog_connect", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("dialog_connect", "IP", nullptr));
        pushButton->setText(QCoreApplication::translate("dialog_connect", "PushButton", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("dialog_connect", "11451", nullptr));
        lineEdit->setText(QCoreApplication::translate("dialog_connect", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("dialog_connect", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog_connect: public Ui_dialog_connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONNECT_H
