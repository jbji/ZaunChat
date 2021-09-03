#include "tcpserver.h"
#include "Network/tcpclientsocket.h"
#include "server.h"
#include "servercontroller.h"
TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

//TcpServer最重要的就是incommingConnection.
void TcpServer::incomingConnection ( qintptr socketDescriptor )
{
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);//设置本socket唯一标识符
    //建议把登录超时就结束连接的功能做在客户端.
}
