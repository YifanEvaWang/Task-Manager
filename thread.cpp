#include "thread.h"

Thread::Thread(QObject *parent, qintptr id): QThread(parent)
{
    this->socketDescriptor = id;
}

void Thread::run()
{
    qDebug() << socketDescriptor << "Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)){
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "Connected!";

    exec();
}

void Thread::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << socketDescriptor << "Input a message:" << data;
    socket->write(data);
    MainWindow win;
//    foreach (QWidget *widget, QApplication::topLevelWidgets())
//    {
//        if (typeid(widget)==typeid(MainWindow))
//                win = widget;
//    }
//    win.addItemToChattingRoom(socketDescriptor,data);
}

void Thread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket -> deleteLater();
    exit(0);
}


