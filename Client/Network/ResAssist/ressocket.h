#ifndef RESSOCKET_H
#define RESSOCKET_H


#include "Network/tcpclientsocket.h"

//用于托管专门收发文件的socket

class ResSocket : public TcpClientSocket
{
    Q_OBJECT
public:
    explicit ResSocket(QObject *parent = nullptr);

    void AbortConnection();
    void ConnectToServer();
    static ResSocket* GetSocket();

signals:
    void receivingThings();
public slots:
    virtual void receiveMessage();
private:
    static ResSocket * socket;
};

#endif // RESSOCKET_H
