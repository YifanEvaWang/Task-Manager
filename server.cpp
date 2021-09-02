#include "server.h"

Server::Server(QObject *parent): QTcpServer(parent)
{

}

void Server:: startServer()
{
    if(!this->listen(QHostAddress::Any, 8000))
    {
        qDebug() << "error starting server";
    }
    else
    {
        qDebug() <<"listening...";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << "connecting...";
    Thread *thread = new Thread(this, socketDescriptor);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
