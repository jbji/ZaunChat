#ifndef RESSERVER_H
#define RESSERVER_H


#include <QObject>
#include "Network/tcpclientsocket.h"
#include "Network/Server/tcpserver.h"
#include <QMap>
class ResServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ResServer(QObject *parent = 0);
    void start(int port);
    void stop();
    virtual void incomingConnection ( qintptr socketDescriptor );
};

#endif // RESSERVER_H
