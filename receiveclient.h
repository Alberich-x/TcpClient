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




//客户端实现
//通过新建dialog_connect的ui来完成connectToHost操作
//总共分为三个线程, 主线程, MyThread线程接收缓存, FileThread线程读写文件
//接收缓存过程: 接收信号, 判断是否为头文件, 推入缓存, 缓存判断是否传输完毕, 推送缓存采用timer,每10ms判断一次是否有缓存
//读写文件过程: 接收文件头, 根据文件头创建文件, 同时判断是否存在路径并新建, 剩下的数据即为文件内容
//线程之间通过槽信号传输

//遗留问题:
//1.多客户端连接有问题
//2.服务端不能在接收数据后再次接收信号


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

    //处理界面
    void tbVisible();
    void folderPathSelect();


    //处理连接窗口
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
    //处理信号

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
    int cnt = 0;                        //计数， 超过十条发送拉取命令(没有用到)
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


    void checkSignal(); //处理到来的信号
    void pullData();    //缓存
    void timeUpPushData();  //推送数据



    void sendWriteCommand();    
    void checkFile();   //检查文件
    void recursionFind(QFileInfoList& list_dir, QDir dir);  //递归寻找文件
    void socketDisconnect();              //disconnect信号触发， 用于提示断开连接
    //void sendContinueInfo();                




signals:
    void sendMessage(QString title, QString content);
    void sendPlainText(QString text);
    void sendLabelText(QString text);
    //按钮空间
    void sendButtonInformation();       
    void sendButtonInformation2();
    //传输时按钮不可用实现
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
