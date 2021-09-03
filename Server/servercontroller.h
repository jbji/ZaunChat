#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H


#include "Network/Server/server.h"
#include "Network/Server/resserver.h"

//类似于server的controller

class ServerController
{
public:
    ServerController();

    static ResServer* getResServerInstance();
    static Server* getServerInstance();//保证连接的是一个数据库
    static TcpClientSocket* GetClient(quint32 Id);
private:
    static Server* _server;
    static ResServer* _resServer;
};

#endif // SERVERCONTROLLER_H
