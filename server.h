#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include "thread.h"
#include "mainwindow.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);


signals:
    void requestAddingItem(QString text);

};

#endif // MYSERVER_H
