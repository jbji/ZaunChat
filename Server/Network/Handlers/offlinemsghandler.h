#pragma once
#include"msghandler.h"

class OffLineMsgHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit OffLineMsgHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};