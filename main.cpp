#include "receiveclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReceiveClient w;
    w.show();
    return a.exec();
}
