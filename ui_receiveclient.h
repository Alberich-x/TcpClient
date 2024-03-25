/********************************************************************************
** Form generated from reading UI file 'receiveclient.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVECLIENT_H
#define UI_RECEIVECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReceiveClient
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *VLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton_7;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textBrowser;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ReceiveClient)
    {
        if (ReceiveClient->objectName().isEmpty())
            ReceiveClient->setObjectName(QString::fromUtf8("ReceiveClient"));
        ReceiveClient->resize(651, 560);
        centralwidget = new QWidget(ReceiveClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 611, 511));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        VLayout = new QVBoxLayout();
        VLayout->setObjectName(QString::fromUtf8("VLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setAutoRepeatDelay(300);
        pushButton_7->setAutoRepeatInterval(100);

        gridLayout->addWidget(pushButton_7, 1, 1, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 0, 1, 1);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 2, 1, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 0, 1, 1, 1);


        VLayout->addLayout(gridLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout_4->addWidget(progressBar);


        VLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));

        VLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(VLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_4->addLayout(horizontalLayout_2);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_4->addWidget(textBrowser);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_2);

        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::NoSelection);

        horizontalLayout->addWidget(tableView);

        ReceiveClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ReceiveClient);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 651, 23));
        ReceiveClient->setMenuBar(menubar);
        statusbar = new QStatusBar(ReceiveClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ReceiveClient->setStatusBar(statusbar);

        retranslateUi(ReceiveClient);

        QMetaObject::connectSlotsByName(ReceiveClient);
    } // setupUi

    void retranslateUi(QMainWindow *ReceiveClient)
    {
        ReceiveClient->setWindowTitle(QCoreApplication::translate("ReceiveClient", "ReceiveClient", nullptr));
        pushButton_7->setText(QCoreApplication::translate("ReceiveClient", "\346\237\245\347\234\213\346\227\245\345\277\227\346\226\207\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("ReceiveClient", "\350\277\236\346\216\245", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ReceiveClient", "\346\216\245\346\224\266\346\226\207\344\273\266", nullptr));
        pushButton_5->setText(QCoreApplication::translate("ReceiveClient", "\346\237\245\347\234\213\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_6->setText(QCoreApplication::translate("ReceiveClient", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        pushButton_4->setText(QCoreApplication::translate("ReceiveClient", "\346\233\264\346\224\271\344\277\235\345\255\230\345\234\260\345\235\200", nullptr));
        label->setText(QCoreApplication::translate("ReceiveClient", "\344\270\213\350\275\275\346\227\245\345\277\227:", nullptr));
        progressBar->setFormat(QString());
    } // retranslateUi

};

namespace Ui {
    class ReceiveClient: public Ui_ReceiveClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVECLIENT_H
