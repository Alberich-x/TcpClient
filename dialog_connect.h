#ifndef DIALOG_CONNECT_H
#define DIALOG_CONNECT_H

#include <ui_dialog_connect.h>
#include <QDialog>
#include <QWidget>
#include <qmainwindow.h>
#include <iostream>
#include <qvalidator.h>
#include <qdebug.h>

//namespace Ui {
//	class untitled;
//}

class dialog_connect : public QDialog
{
	Q_OBJECT
public:
	dialog_connect(QWidget* parent = nullptr);
	~dialog_connect();

signals:
	void senddata(QString ip_n, QString port_n);	//´«»ØipÓëport

private:
	Ui::dialog_connect* ui;
};
#endif // WARNING_EMPTY_H
