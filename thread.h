#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <typeinfo>
#include "mainwindow.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0, qintptr id=0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);
public slots:
    void readyRead();
    void disconnected();
private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // THREAD_H
