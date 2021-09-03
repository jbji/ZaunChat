#include "server.h"
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>
#include "tcpserver.h"
Server::Server(QObject *parent) :
    QObject(parent),
    _tcpServer(new TcpServer)
{

}

void Server::start(int port)
{

    if( false == _tcpServer->listen(QHostAddress::Any,port) )
    {
        QMessageBox::warning(NULL,"错误","无法监听端口, 请检查是否在该端口上启动了其他服务器");
        qDebug()<<_tcpServer->errorString();
    }
}

void Server::stop()
{
    _clients.clear();
    _tcpServer->close();
}

void Server::addClient(quint32 id,TcpClientSocket* c)
{
    _clients[id] = c;
}

TcpClientSocket* Server::getClients(quint32 Id)
{
    if(_clients.find(Id) == _clients.end()) return NULL;
    return _clients[Id];
}
void Server::deleteClient(quint32 id){
    _clients.remove(id);
}
