#include "resserver.h"
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>
#include "Utilities/log.h"
#include "Network/ResAssist/ressocket.h"

ResServer::ResServer(QObject *parent) :
    QTcpServer(parent)
{

}


void ResServer::start(int port)
{

    if( false == listen(QHostAddress::Any,port) )
    {
        QMessageBox::warning(NULL,"资源服务器错误","无法监听端口, 请检查是否在该端口上启动了其他服务器");
    }
}

//TcpServer最重要的就是incommingConnection.
void ResServer::incomingConnection ( qintptr socketDescriptor )
{
    qDebug() << "here";
    TcpClientSocket *tcpClientSocket = new ResSocket(this);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);//设置本socket唯一标识符
    Log::GetLogObj()->writeLog("[Client connect to resserver]");

}

void ResServer::stop()
{
    close();
}
