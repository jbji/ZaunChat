#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include <QObject>
#include "DataModel/Msg/msg.h"
#include "Network/tcpclientsocket.h"


//MsgHandler接口(抽象类), 用于定义对Msg共同的parse行为.

//考虑到MsgHandler可能需要发射emit信号,和潜在地被调用槽函数,
//  因此继承自QObject作为QtObject子类

class MsgHandler : public QObject
{
	Q_OBJECT
public:
    explicit MsgHandler(QObject* parent = nullptr) : QObject(parent){};
	//解析Msg的函数
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr) = 0;
};

#endif // MSGHANDLER_H
