#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>
#include "DataModel/Msg/msg.h"

//code by BFZD

class TcpClientSocket:  public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject *parent = 0);
    void setServerIP(const QString & serverIP);
    void setServerTcpPort(const QString &serverTcpPort);
    QString getServerIP();
    QString getServerPort();
    bool testConnect();
    bool connectToServer();
    void sendMessage(Msg * message);

signals:

public slots:
    virtual void receiveMessage();
protected:
    QString _serverIP;
    int _serverTcpPort;
    quint32 _blockSize;

};

#endif // TCPCLIENTSOCKET_H
