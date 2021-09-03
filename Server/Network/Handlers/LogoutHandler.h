#pragma once
#include"msghandler.h"

class LogoutHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit LogoutHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
