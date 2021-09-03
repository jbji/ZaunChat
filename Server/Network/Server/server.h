#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "Network/tcpclientsocket.h"
#include "Network/Server/tcpserver.h"
#include <QMap>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void start(int port);
    void  stop();
    void addClient(quint32 id,TcpClientSocket* c);
    void deleteClient(quint32 id);
    TcpClientSocket* getClients(quint32 Id);
signals:

public slots:


private:
    TcpServer* _tcpServer;
    QMap<quint32,TcpClientSocket*> _clients;

};

#endif // SERVER_H
