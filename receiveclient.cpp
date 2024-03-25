#include "receiveclient.h"
#include "ui_receiveclient.h"
QSemaphore order(1);
bool FILE_IS_OPEN;

ReceiveClient::ReceiveClient(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::ReceiveClient)
{

	//设置tableView样式
	ui->setupUi(this);
	qDebug() << this->thread();
	//ui->progressBar->setVisible(false);
	model = new QStandardItemModel();
	model->insertColumns(0, 4);
	model->setHeaderData(0, Qt::Horizontal, tr(u8"文件名"));
	model->setHeaderData(1, Qt::Horizontal, tr(u8"文件大小"));
	model->setHeaderData(2, Qt::Horizontal, tr(u8"下载时间"));
	model->setHeaderData(3, Qt::Horizontal, tr(u8"文件位置"));
	ui->tableView->setModel(model);
	QStringList headerstring;
	ui->label->setFixedWidth(80);
	ui->label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	ui->tableView->verticalHeader()->setVisible(false);
	ui->tableView->show();
	ui->pushButton_2->setStyleSheet("color:grey");
	ui->pushButton_6->setStyleSheet("color:grey");
	ui->pushButton_2->setEnabled(false);
	ui->pushButton_6->setEnabled(false);
	//菜单栏设计
	QMenu* menu_add = menuBar()->addMenu(u8"New");
	QAction* action_connect = new QAction(QIcon("./Icon/connect.png"), tr("New Connect"), this);
	action_connect->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	menu_add->addAction(action_connect);

	dialog_c = new dialog_connect();


	//connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(showConnectDialog()));;
	//connect(action_connect, SIGNAL(triggered()), this, SLOT(showConnectDialog()));
	connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
		qDebug() << "Safe.";
		dialog_c->show();
		});
	connect(action_connect, &QAction::triggered, this, [this]() {
		dialog_c->show();
		});
	//connect(dialog_c, &dialog_connect::senddata, this, &ReceiveClient::sendHostAddressS);
	connect(dialog_c, &dialog_connect::senddata, this, [this](QString a, QString b)
		{
			emit sendHostAddress(a, b.toInt());
		});
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(folderPathSelect()));
	connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(checkFolder()));

	connect(ui->pushButton_7, &QPushButton::clicked, this, &ReceiveClient::checklogging);
	connect(ui->tableView, &QTableView::doubleClicked, this, &ReceiveClient::openTableView);
	processTheConnect();

}


void ReceiveClient::processTheConnect()
{
	qRegisterMetaType<QVector<QByteArray>>("QVector<QByteArray>");
	qRegisterMetaType<QVector<QTextCursor>>("QTextCursor");
	//_serverAddress = a;
	//_serverPort = b.toInt();
	
	MyThread* thread1 = new MyThread();
	thread1->moveToThread(thread1);
	qDebug() << "Thread1: " << thread1->thread();
	thread1->start();


	connect(this, &ReceiveClient::sendHostAddress, thread1, &MyThread::socketConnect);
	connect(this, &ReceiveClient::sendDirPath, thread1, [thread1](QString dirpath) {
		thread1->_dirPath = dirpath;
		});


	connect(thread1, &MyThread::sendMessage, this, &ReceiveClient::message);
	connect(thread1, &MyThread::sendPlainText, this, &ReceiveClient::insertPlain);
	connect(thread1, &MyThread::sendButtonInformation, this, &ReceiveClient::buttonEnabled);
	connect(thread1, &MyThread::sendButtonInformation2, this, &ReceiveClient::buttonEnabledReverse);
	connect(thread1, &MyThread::sendTransBtnEnabled, this, &ReceiveClient::btnTransEnabled);
	connect(thread1, &MyThread::sendTransBtnDisabled, this, &ReceiveClient::btnTransDisabled);
	connect(thread1, &MyThread::sendLabelText, this, &ReceiveClient::labelText);
	connect(ui->pushButton_2, &QPushButton::clicked, thread1, &MyThread::sendSignalNum1);
	connect(ui->pushButton_6, &QPushButton::clicked, thread1, &MyThread::disConnect);
	//emit sendHostAddress(a, _serverPort);

	FileThread* thread2 = new FileThread();
	thread2->moveToThread(thread2);
	qDebug() << "Thread2: " << thread2->thread();
	thread2->start();
	emit sendDirPath(_dirPath);
	connect(this, &ReceiveClient::sendDirPath, thread2, [thread2](QString dirpath) {
		thread2->_dirPath = dirpath;
		});


	connect(thread1, &MyThread::sendDataSignal, thread2, &FileThread::receiveBuffer);
	connect(thread2, &FileThread::sendMessage, this, &ReceiveClient::message);
	connect(thread2, &FileThread::sendDisconnect, thread1, &MyThread::disConnect);
	connect(thread2, &FileThread::sendSignal, thread1, &MyThread::sendSignalNum);
	connect(thread2, &FileThread::sendModel, this, &ReceiveClient::editModel);
	connect(thread2, &FileThread::sendEndMessage, thread1, &MyThread::timerEnd);
	connect(thread2, &FileThread::sendCheck, thread1, &MyThread::checkLocalFile);
	connect(thread2, &FileThread::sendProgressBarValue, this, &ReceiveClient::changeProgressBarValue);
	connect(thread2, &FileThread::sendProgressBarRange, this, &ReceiveClient::changeProgressBarRange);
	connect(thread2, &FileThread::sendLabelText, this, &ReceiveClient::labelText);
	connect(thread2, &FileThread::sendProgressBarUnvisible, this, &ReceiveClient::changeProgressBarUnvisible);
	connect(thread2, &FileThread::sendPlainText, this, &ReceiveClient::insertPlain);

	return;
	//socketConnect();
}



ReceiveClient::~ReceiveClient()
{
	delete ui;
}

//进行连接，同时避免重复连接和连接不上.
void MyThread::socketConnect(QString _serverAddress,int _serverPort)
{
	qDebug() << _dirPath;
	//qDebug() << this->thread();
	_address = _serverAddress;
	_port = _serverPort;
	qDebug() << "HA: " << _serverAddress <<  " HP: " << _serverPort;
	if (socket == nullptr)
	{
		socket = new QTcpSocket();
		socket->moveToThread(this);
		socket->setProxy(QNetworkProxy::NoProxy);
	}
	else
	{
		socket->moveToThread(this);
		socket->setProxy(QNetworkProxy::NoProxy);
	}
	//判断是否为空指针导致程序崩溃
	//if (socket == nullptr) {
	//	socket = new QTcpSocket();
	//	socket->setProxy(QNetworkProxy::NoProxy);
	//}
	////确保不重复连接导致错误，然后进行连接
	if (socket->state() != QAbstractSocket::ConnectedState)
	{
		qDebug() << "Try to connect" << socket->thread();
		socket->connectToHost(_serverAddress, _serverPort);
		socket->waitForConnected(10);
		//判断是否有连接上.
		if (socket->state() == QAbstractSocket::ConnectedState)
		{
			emit sendMessage("Information", "Connected");
			qDebug() << "Connect to the server:" << _serverAddress;
			emit sendPlainText("Connect to ip: " + _serverAddress + "\n");
			connect(socket, &QTcpSocket::disconnected, this, &MyThread::socketDisconnect);
			connect(socket, &QTcpSocket::readyRead, this, &MyThread::checkSignal);
			emit sendButtonInformation();
		}
		else
		{
			QString temp_solve;
			temp_solve = "Can't connect to server:" + _serverAddress + socket->errorString();
			delete socket;
			socket = new QTcpSocket;
			qDebug() << "Can't connect to server:" + _serverAddress + socket->errorString() << socket->thread();
			emit sendMessage("Error", temp_solve);
		}
	}
	else
	{
		qDebug() << "Cann't connect to server twice.";
	}

}




//断开连接后弹出QMessage.
void MyThread::socketDisconnect()
{
	qDebug() << "Disconnect form ip: " + _address + "\n";

	emit sendPlainText("Disconnect form ip: " + _address + "\n");
	emit sendMessage("Disconnected.", "Disconnect form ip: " + _address + "\n");
	emit sendButtonInformation();
	emit sendButtonInformation2();
	//delete socket;
	socket->deleteLater();
	socket = nullptr;
}


void MyThread::checkSignal()
{
	//qDebug() << "Receive the signal.";

	if (_flagTrans)
	{
		//qDebug() << socket->size();
		pullData();
	}
	else
	{
		qint64 signal_this;
		QDataStream in(&_downBytesArrayRecieved, QIODevice::ReadWrite);
		_downBytesArrayRecieved.resize(0);
		in.device()->reset();
		_downBytesArrayRecieved.append(socket->readAll());
		in >> signal_this >> _fileNumber >> _downSizeReveiced;
		//qDebug() << "signal_this: " << signal_this << "SizeReceived: " << socket->size() + 8;

		if (timer_flag)
		{
			timer_flag = false;
			timer->start(10);
		}
		switch (signal_this)
		{
		case 0: {
			_downBytesArrayRecieved = _downBytesArrayRecieved.right(_downBytesArrayRecieved.size() - sizeof(qint64));
			checkFile();
			break;
		}

		case 1: {
			in.device()->reset();
			_flagTrans = true;
			emit sendTransBtnDisabled();
			_fileNumberReceived++;
			//qDebug() << _fileNumberReceived << "/" << _fileNumber;
			QString labelText = QString::number(_fileNumberReceived) + "/" + QString::number(_fileNumber);
			sendLabelText(labelText);
			_downBytesArrayRecieved = _downBytesArrayRecieved.right(_downBytesArrayRecieved.size() - sizeof(qint64)*2);
			_downSizeReveiced -= _downBytesArrayRecieved.size();
			buffer.push_back(_downBytesArrayRecieved);
			break;
		}
		case 2:
		{
			break;
		}
		case 3:

		default:
			qDebug() << "Something wrong.";
			break;
		}
	}
}
void ReceiveClient::enableButton()
{
	ui->pushButton_2->setStyleSheet("color:black");
	ui->pushButton_2->setEnabled(true);
}





void MyThread::checkFile()
{
	emit sendPlainText(u8"校验中...\n");
	checkLocalFile();
	QDataStream datastream(_downBytesArrayRecieved);
	//qDebug() << _downBytesArrayRecieved;
	_downBytesArrayRecieved = _downBytesArrayRecieved;
	QByteArray hashCodeReceived = _downBytesArrayRecieved;
	_downBytesArrayRecieved.resize(0);
	if (_hashCode == hashCodeReceived)
	{
		sendPlainText(u8"文件无损坏\n");
		sendMessage(u8"校验完成", u8"文件无损坏");
	}
	else
	{
		sendPlainText(u8"校验异常\n");
		sendMessage(u8"校验完成", u8"校验异常");
	}
	emit sendLabelText(u8"下载完成:");// + QString::number(_fileNumberReceived) + "/" + QString::number(_fileNumber));
	emit sendTransBtnEnabled();
	_fileNumberReceived = 0;
}



void MyThread::checkLocalFile()
{
	//qDebug() << "debug";
	QCryptographicHash hash(QCryptographicHash::Md5);
	QString dir_path = _dirPath;
	QDir dir(dir_path);
	QFileInfoList list_dir;
	QVector<QString> filename_list;
	recursionFind(list_dir, dir);
	foreach(QFileInfo fileinfo, list_dir)
	{
		filename_list.push_back(fileinfo.path() + "/" + fileinfo.fileName());
	}
	foreach(QString fileName_this, filename_list)
	{
		QFile* file_check = new QFile(fileName_this);
		file_check->open(QIODevice::ReadOnly);
		hash.addData(file_check);
		filename_list.pop_front();
		file_check->close();
	}
	_hashCode = hash.result().toHex();
	qDebug() << u8"Md5校验结果: "<< hash.result().toHex();

	return;
}

void MyThread::recursionFind(QFileInfoList& list_dir, QDir dir)
{
	QStringList list_temp;
	QFileInfoList list_dir_temp;
	qDebug() << dir;
	if (!dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot).isEmpty())
	{
		list_temp = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		foreach(QString text_temp, list_temp)
		{
			qDebug() << "Dirs: " << text_temp;
			if (dir.cd(text_temp));
			{
				qDebug() << dir.path();
				recursionFind(list_dir, dir);
				dir.cdUp();
			}
		}
	}
	else
		qDebug() << "No directions here: " << dir.path();

	if (!dir.entryInfoList(QDir::Files).isEmpty())
	{
		list_dir_temp = dir.entryInfoList(QDir::Files);
		foreach(QFileInfo fi, list_dir_temp)
			list_dir.push_back(fi);
	}
	return;

}







void FileThread::receiveFile()
{
	QDataStream in(&_downBytesArrayRecieved, QIODevice::ReadWrite);
	in.setVersion(QDataStream::Qt_5_14);
	//判断是否为头文件并处理
	if (qint64(_downBytesRecieved) < qint64(sizeof(qint64) * 2) )//&& _downBytesArrayRecieved.size())
	{
		timer_timing.restart();
		qint64 trans_num;
		qDebug() << u8"文件创建";
		in >> _downFileSize >> _downFileNameSize;									//读入信息
		qDebug() << qint64(_downFileSize) << qint64(_downFileNameSize);
		_downBytesRecieved += sizeof(qint64) * 2;
		if (_downBytesArrayRecieved.size() >= _downFileNameSize && _downFileNameSize != 0)
		{
			in >> _downFileName;														//剩下的string则为文件名。
			_downBytesArrayRecieved = _downBytesArrayRecieved.right(_downBytesArrayRecieved.size() - _downFileNameSize);
			//emit sendLabelText(_downFileName + ":");
			_downFileName = _dirPath + _downFileName;							//完善存储地址
			_downBytesRecieved += _downFileNameSize;									//已接收文件大小.
			_downloadFile = new QFile(_downFileName);									//新建对象
			//emit sendPlainText("Receive files " + _downFileName + " from " + _serverAddress + "\n");
			emit sendProgressBarRange(_downFileSize / 1024 / 1024);
			emit sendProgressBarValue(_downBytesRecieved/1024/1024);
			_downBytesArrayRecieved = _downBytesArrayRecieved.right(_downBytesArrayRecieved.size() - _downBytesRecieved);
			qDebug() << _downFileName;
			QString folderPath = _downFileName.left(_downFileName.lastIndexOf('/'));

			QDir dir;
			if (!dir.exists(folderPath))
			{
				if(dir.mkpath(folderPath.right(folderPath.size() )))
					qDebug() << "Make the direction:" << folderPath.right(folderPath.size() );
				else
				qDebug() << folderPath.right(folderPath.size() );
			}
			else
			{
				qDebug() << "Folder existed.";
			}



			if (!_downloadFile->open(QFile::WriteOnly))									//测试是否能打开文件.
			{
				emit sendMessage("Warning", u8"无法打开文件");
				emit sendDisconnect();
				qDebug() << "Error to open the file:" << _downFileName;
			}
			else
			{
				FILE_IS_OPEN = true;
				qDebug() << _downFileName << "Has opened.";
				_downBytesArrayRecieved = _downBytesArrayRecieved.right(_downBytesArrayRecieved.size() - _downBytesRecieved);
			}
		}
		else
		{
			qDebug() << "Something wrong. Filename:" << _downFileName << "FileSize:" << _downFileSize;
			return;
		}
	}

	if (_downBytesRecieved <= _downFileSize && _downBytesArrayRecieved.size() > 0)
	{
		 {
			_downBytesRecieved += _downBytesArrayRecieved.size();
			_downloadFile->write(_downBytesArrayRecieved);
			_downBytesArrayRecieved.resize(0);
			//根据已经下载的大小调整progressBar的进度条
			//qDebug() << _downBytesRecieved << _downFileSize;
			emit sendProgressBarValue(_downBytesRecieved / 1024 / 1024);
		}
	}
	//判断是否下载完成
	if (_downBytesRecieved >= _downFileSize)
	{
		if (FILE_IS_OPEN)
		{
			_downloadFile->close();
			FILE_IS_OPEN = false;
		}
		//文件下载完毕后记录
		//emit sendLabelText(u8"日志:");
		emit sendProgressBarUnvisible();
		qDebug() << _downFileName << u8"下载完成 ";
		QString timeDown = QString::number(static_cast<float>(timer_timing.elapsed()) / 1000) + "s";
		emit sendModel(timeDown, _downFileName, _downFileSize, _downBytesRecieved);


		logging("Receive files " + _downFileName + " from " + _serverAddress + "\n");
		_downBytesRecieved = 0;
		_downFileSize = -1;
		_downFileName = "";
		sendSignal(2);
		emit sendProgressBarRange(1);
		emit sendProgressBarValue(1);
	}

}

void FileThread::receiveBuffer(QVector<QByteArray> buffer)
{
	while (!buffer.isEmpty())
	{
		_downBytesArrayRecieved = buffer[0];
		buffer.pop_front();
		receiveFile();
	}
}



void MyThread::sendSignalNum(qint64 num)
{
	//0:校验, 1:文件发送请求, 2:读取完一个文件发送的信号
	QByteArray outblock;
	QDataStream datastream(&outblock, QIODevice::ReadWrite);
	datastream << qint64(0);
	datastream.device()->seek(0);
	datastream << qint64(num);
	//qDebug() << "Sent the signal: " << num;
	socket->write(outblock);
	socket->flush();
}

void MyThread::sendSignalNum1()
{
	//0:校验, 1:文件发送请求, 2:读取完一个文件发送的信号
	QByteArray outblock;
	QDataStream datastream(&outblock, QIODevice::ReadWrite);
	datastream << qint64(0);
	datastream.device()->seek(0);
	datastream << qint64(1);
	//qDebug() << "Sent the signal: " << qint64(1);
	socket->write(outblock);
	socket->flush();
	socket->waitForReadyRead();
}


void ReceiveClient::showConnectDialog()
{
	//qDebug() << "Show Dialog.";
	dialog_c->show();
}




void ReceiveClient::editModel(QString timeDown, QString _downFileName, qint64 _downFileSize, qint64 _downBytesRecieved)
{
	model->setItem(_rowCount, 0, new QStandardItem(_downFileName.right(_downFileName.size() - _downFileName.lastIndexOf('/') - 1)));
	QString downloadSize =
		_downFileSize < 1024 ? QString::number(_downBytesRecieved) + "B" :
		_downFileSize < 1024 * 1024 ? QString::number(static_cast<float>(_downBytesRecieved / 1024), 'f', 1) + "KB" :
		_downFileSize < 1024 * 1024 * 1024 ? QString::number(static_cast<float>(_downBytesRecieved / 1024) / 1024, 'f', 1) + "MB" : QString::number(static_cast<float>(_downBytesRecieved / 1024 / 1024) / 1024, 'f', 1) + "GB";
	if (downloadSize.at(downloadSize.length() - 3) == "0")
	{
		downloadSize.remove(downloadSize.length() - 4, 2);
	}
	model->setItem(_rowCount, 1, new QStandardItem(downloadSize));
	model->setItem(_rowCount, 2, new QStandardItem(timeDown));
	model->setItem(_rowCount, 3, new QStandardItem(_downFileName));
	_rowCount++;
	logging("Receive files " + _downFileName + " from " + _serverAddress + "\n");
	ui->textBrowser->insertPlainText("Receive files " + _downFileName + " from " + _serverAddress + "\n");
	QTextCursor cursor = ui->textBrowser->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->textBrowser->setTextCursor(cursor);

}



void MyThread::disConnect()
{
	socket->disconnectFromHost();
	
	//qDebug() << "DisConnect()";
}






void ReceiveClient::tbVisible()
{
	if (ui->textBrowser->isHidden())
		ui->textBrowser->show();
	else
		ui->textBrowser->hide();
}

void ReceiveClient::folderPathSelect()
{
	_dirPath = QFileDialog::getExistingDirectory(nullptr, tr(u8"打开文件夹"), QDir::homePath()) + "/";
	ui->textBrowser->insertPlainText("切换保存位置为: " + _dirPath);
	QTextCursor cursor = ui->textBrowser->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->textBrowser->setTextCursor(cursor);
	emit sendDirPath(_dirPath);
}


void ReceiveClient::checkFolder()
{
	QDesktopServices::openUrl(QUrl("file:" + _dirPath, QUrl::TolerantMode));

}


void ReceiveClient::checklogging()
{
	QDesktopServices::openUrl(QUrl("file:./log.txt", QUrl::TolerantMode));
}

void ReceiveClient::changeProgressBarValue(int value)
{
	ui->progressBar->setValue(value);
}

void ReceiveClient::changeProgressBarRange(int range)
{
	ui->progressBar->setVisible(true);
	ui->progressBar->setRange(0, range);
}

void ReceiveClient::changeProgressBarUnvisible()
{
	ui->progressBar->setTextVisible(false);
}


void ReceiveClient::labelText(QString text)
{
	ui->label->setText(text);
}

void ReceiveClient::openTableView(const QModelIndex& index_this)
{
	int row = index_this.row();
	QModelIndex index_filepath = model->index(row, 3);
	QVariant filepath = model->data(index_filepath);
	QString filepath_string = filepath.toString();
	QDesktopServices::openUrl(QUrl("file:" + filepath_string, QUrl::TolerantMode));
}

void ReceiveClient::deleteThread()
{

}








void ReceiveClient::logging(QString message_log)
{
	QDateTime dateTime = QDateTime::currentDateTime();//获取系统当前的时间
	QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss") + ": ";//格式化时间
	message_log = str + message_log;
	QString file_log = "log.txt";
	QFile file(file_log);
	if (file.exists())
	{
		if (!file.open(QIODevice::Append | QIODevice::Text))
		{
			qDebug() << "Can't open the log file.";
		}
		QTextStream in_text(&file);
		in_text << message_log;
	}
	else
	{
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream in_text(&file);
		in_text << message_log;
	}
	return;
}

void MyThread::logging(QString message_log)
{
	QDateTime dateTime = QDateTime::currentDateTime();//获取系统当前的时间
	QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss") + ": ";//格式化时间
	message_log = str + message_log;
	QString file_log = "log.txt";
	QFile file(file_log);
	if (file.exists())
	{
		if (!file.open(QIODevice::Append | QIODevice::Text))
		{
			qDebug() << "Can't open the log file.";
		}
		QTextStream in_text(&file);
		in_text << message_log;
	}
	else
	{
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream in_text(&file);
		in_text << message_log;
	}
	return;
}
void FileThread::logging(QString message_log)
{
	QDateTime dateTime = QDateTime::currentDateTime();//获取系统当前的时间
	QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss") + ": ";//格式化时间
	message_log = str + message_log;
	QString file_log = "log.txt";
	QFile file(file_log);
	if (file.exists())
	{
		if (!file.open(QIODevice::Append | QIODevice::Text))
		{
			qDebug() << "Can't open the log file.";
		}
		QTextStream in_text(&file);
		in_text << message_log;
	}
	else
	{
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream in_text(&file);
		in_text << message_log;
	}
	return;
}



void ReceiveClient::message(QString title, QString content)
{
	QMessageBox::information(this, title, content);
}


void ReceiveClient::insertPlain(QString content)
{
	ui->textBrowser->insertPlainText(content);
	QTextCursor cursor = ui->textBrowser->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->textBrowser->setTextCursor(cursor);
}

void ReceiveClient::buttonEnabled()
{
	ui->pushButton->setStyleSheet("color:grey");
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setStyleSheet("color:black");
	ui->pushButton_6->setStyleSheet("color:black");
	ui->pushButton_2->setEnabled(true);
	ui->pushButton_6->setEnabled(true);
}

void ReceiveClient::buttonEnabledReverse()
{
	ui->pushButton->setStyleSheet("color:black");
	ui->pushButton->setEnabled(true);
	ui->pushButton_2->setStyleSheet("color:grey");
	ui->pushButton_6->setStyleSheet("color:grey");
	ui->pushButton_2->setEnabled(false);
	ui->pushButton_6->setEnabled(false);
}


void ReceiveClient::btnTransEnabled()
{
	ui->pushButton_2->setStyleSheet("color:black");
	ui->pushButton_2->setEnabled(true);
}

void ReceiveClient::btnTransDisabled()
{
	ui->pushButton_2->setStyleSheet("color:grey");
	ui->pushButton_2->setEnabled(false);
}




void MyThread::pullData()
{
	_downSizeReveiced -= socket->size();
	buffer.push_back(socket->readAll());
	if (_downSizeReveiced <= 0){
		_flagTrans = false;
		qDebug() << "Tranport done.";
	}
	else {
	}
}

void MyThread::timeUpPushData()
{
	if (!buffer.isEmpty())
	{
		emit sendDataSignal(buffer);
		buffer.clear();
		//发送并清空buffer
	}
	else
	{
	}
	timer->start(10);
}

void MyThread::timerEnd()
{
	timer->stop();
}



void MyThread::run()
{
	//此处应是分配socket对象.t
	timer = new QTimer();
	timer->moveToThread(this);
	connect(timer, &QTimer::timeout, this, &MyThread::timeUpPushData);
	exec();
}

