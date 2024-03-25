#include <dialog_connect.h>

dialog_connect::dialog_connect(QWidget* parent)
	:QDialog(parent), ui(new Ui::dialog_connect)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
		emit senddata(ui->lineEdit->text(), ui->lineEdit_2->text());
		close();
		});
}

dialog_connect::~dialog_connect()
{
	qDebug() << "Delete accidently.";
	delete ui;
}
