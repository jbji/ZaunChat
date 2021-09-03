#include "tcpclientsocket.h"
#include <QHostAddress>
#include <QDataStream>
#include "Utilities/log.h"
#include "handlerreg.h"
#include <QString>
TcpClientSocket::TcpClientSocket(QObject *parent) :
    QTcpSocket(parent),_blockSize(0)
{
    connect(this, SIGNAL(readyRead()),this, SLOT(receiveMessage()));
}
void TcpClientSocket::setServerIP(const QString & serverIP)
{
    _serverIP = serverIP;
}

void TcpClientSocket::setServerTcpPort(const QString & serverTcpPort)
{
    _serverTcpPort = serverTcpPort.toInt();
}

QString TcpClientSocket::getServerIP()
{
    return _serverIP;
}

QString TcpClientSocket::getServerPort()
{
    return QString::number(_serverTcpPort);
}

bool TcpClientSocket::testConnect()
{
    disconnectFromHost();
    connectToHost(QHostAddress(this->_serverIP),this->_serverTcpPort);
    bool ret = waitForConnected();
    disconnectFromHost();
    return ret;
}

bool TcpClientSocket::connectToServer()
{
    bool ret = true;
    abort();
    connectToHost(QHostAddress(this->_serverIP),this->_serverTcpPort);
    return ret;
}

void TcpClientSocket::sendMessage(Msg* message)
{
    waitForBytesWritten();
    write(message->toQByteArray());
}

void TcpClientSocket::receiveMessage()
{

    QDataStream in(this);

    //取得消息的大小
    if(_blockSize == 0){
        if(bytesAvailable() < (int)sizeof(quint32) ){
            return;
        }
        in >> _blockSize;
    }

    //取得剩余没有读取部分的大小, 如果剩余部分过小 则退出后等待下次读取
    quint32 remainingSize = bytesAvailable();
    if(remainingSize < _blockSize){
        return;
    }

    //读取消息
    quint32 head;
    in >> head;
    if(head == Msg::msgHead){
        _blockSize = _blockSize - sizeof(quint32);
        QByteArray buf;
        buf.reserve(_blockSize);
        //曲线救国
        while(_blockSize > 0){
            quint8 tmp;
            in >> tmp;
            buf.append(tmp);
            _blockSize -= 1;
        }
        Msg tmp = Msg::fromQByteArray(buf);
        HandlerReg::GetRegObj()->getHandler(tmp.getType())
                ->parse(tmp);
    }

    _blockSize = 0;
    if(bytesAvailable() > 0){
        this->receiveMessage();
    }
}

