#ifndef RESSOCKET_H
#define RESSOCKET_H

#include "Network/tcpclientsocket.h"
#include "DataModel/datamodel.h"

class ResSocket : public TcpClientSocket
{
    Q_OBJECT
public:
    explicit ResSocket(QObject *parent = nullptr);

public slots:
    virtual void receiveMessage();

};

#endif // RESSOCKET_H
