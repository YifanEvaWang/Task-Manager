/* Author: Yifan(Emma) Wang
 * Date: Sept 1st 2021
 * reference:
 * https://stackoverflow.com/questions/16474099/qobject-connect-cannot-queue-arguments-of-type-qitemselection
 * https://www.youtube.com/watch?v=iKtCXUHsV70&t=1224s
  */

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
    QString text = QString::fromUtf8(data);
    emit requestAddingItem(text);
}

void Thread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket -> deleteLater();
    exit(0);
}


