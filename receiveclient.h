#ifndef RECEIVECLIENT_H
#define RECEIVECLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetWorkProxy>
#include <qiodevice.h>
#include <qiodevice.h>
#include <qtcpserver.h>
#include <qfiledialog.h>
#include <qsemaphore.h>
#include <qmessagebox.h>
#include <qstandarditemmodel.h>
#include <QNetworkProxy>
#include <dialog_connect.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include <qtextbrowser.h>
#include <qdesktopservices.h>
#include <time.h>
#include <QDateTime>
#include <MD5.h>
#include <qthread.h>
#include <qcryptographichash.h>


QT_BEGIN_NAMESPACE
namespace Ui { class ReceiveClient; }
QT_END_NAMESPACE




//�ͻ���ʵ��
//ͨ���½�dialog_connect��ui�����connectToHost����
//�ܹ���Ϊ�����߳�, ���߳�, MyThread�߳̽��ջ���, FileThread�̶߳�д�ļ�
//���ջ������: �����ź�, �ж��Ƿ�Ϊͷ�ļ�, ���뻺��, �����ж��Ƿ������, ���ͻ������timer,ÿ10ms�ж�һ���Ƿ��л���
//��д�ļ�����: �����ļ�ͷ, �����ļ�ͷ�����ļ�, ͬʱ�ж��Ƿ����·�����½�, ʣ�µ����ݼ�Ϊ�ļ�����
//�߳�֮��ͨ�����źŴ���

//��������:
//1.��ͻ�������������
//2.����˲����ڽ������ݺ��ٴν����ź�


class ReceiveClient : public QMainWindow
{
    Q_OBJECT


signals:
    void sendHostAddress(QString hostAddress, int hostPort);


public:
    ReceiveClient(QWidget *parent = nullptr);
    ~ReceiveClient();
    //void processTheConnect(QString a, QString b);
    void processTheConnect();

private:
    Ui::ReceiveClient *ui;
    dialog_connect* dialog_c;


    unsigned int _serverPort = 11451;
    QString _serverAddress = "127.0.0.1";
    QString _dirPath = "./file_client/";
    QStandardItemModel *model;



    int _rowCount = 0;

    QByteArray info_block = 0;


    void logging(QString message_log);

private slots:
    void enableButton();

    //�������
    void tbVisible();
    void folderPathSelect();


    //�������Ӵ���
    void showConnectDialog();

    void checkFolder();
    void checklogging();

    void message(QString title, QString content);
    void insertPlain(QString content);
    void openTableView(const QModelIndex &index_this);

    void buttonEnabled();
    void buttonEnabledReverse();

    void btnTransDisabled();
    void btnTransEnabled();
    //�����ź�

    void editModel(QString timedown, QString _downFileName, qint64 _downFileSize, qint64 _downBytesRecieved);


    void labelText(QString text);
    void changeProgressBarValue(int value);
    void changeProgressBarRange(int range);
    void changeProgressBarUnvisible();

    void deleteThread();
signals:
    void sendDirPath(QString dirPath);
};

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread() {};
    ~MyThread() {};
    void run() override;
    void socketConnect(QString _serverAddress, int _serverPort);
    void disConnect();
    void sendSignalNum(qint64 num);
    void sendSignalNum1();
    void timerEnd();
    void checkLocalFile();

    QString _dirPath = "./file_client/";
private:
    QTcpSocket *socket = nullptr;
    QByteArray _downBytesArrayRecieved;
    qint64 _downSizeReveiced;
    int cnt = 0;                        //������ ����ʮ��������ȡ����(û���õ�)
    QVector<QByteArray> buffer;
    QString _serverAddress;
    int _serverPort;
    QByteArray _hashCode;

    bool _flagTrans = false;
    QTimer *timer;
    bool timer_flag = true;
    qint64 _fileNumber;
    qint64 _fileNumberReceived = 0;
    QString _address;
    int _port;



    void logging(QString message_log);


    void checkSignal(); //���������ź�
    void pullData();    //����
    void timeUpPushData();  //��������



    void sendWriteCommand();    
    void checkFile();   //����ļ�
    void recursionFind(QFileInfoList& list_dir, QDir dir);  //�ݹ�Ѱ���ļ�
    void socketDisconnect();              //disconnect�źŴ����� ������ʾ�Ͽ�����
    //void sendContinueInfo();                




signals:
    void sendMessage(QString title, QString content);
    void sendPlainText(QString text);
    void sendLabelText(QString text);
    //��ť�ռ�
    void sendButtonInformation();       
    void sendButtonInformation2();
    //����ʱ��ť������ʵ��
    void sendTransBtnDisabled();
    void sendTransBtnEnabled();
    
    void sendDisconnectEvent();
    void sendDataSignal(QVector<QByteArray> buffer);

    void sendDeletesignal();
};



class FileThread: public QThread
{
    Q_OBJECT
public:
    FileThread() {};
    ~FileThread() {};
    void receiveFile();
    void receiveBuffer(QVector<QByteArray> buffer);
    QString _dirPath = "./file_client/";

private:
    QString _serverAddress;

    QString _downFileName;
    qint64 _downBytesRecieved = 0;
    qint64 _downFileSize = 0;
    qint64 _downFileNameSize = 0;;
    QFile *_downloadFile;
    QByteArray _downBytesArrayRecieved;
    QElapsedTimer timer_timing;

    void logging(QString message_log);


signals:
    void sendMessage(QString title, QString content);
    void sendDisconnect();
    void sendSignal(qint64 signal);
    void sendCheck();

    void sendModel(QString timedown, QString _downFileName, qint64 _downFileSize, qint64 _downBytesRecieved);
    void sendEndMessage();

    void sendLabelText(QString text);
    void sendProgressBarValue(int value);
    void sendProgressBarRange(int range);

    void sendProgressBarUnvisible();
    void sendPlainText(QString text);
};



#endif // RECEIVECLIENT_H
