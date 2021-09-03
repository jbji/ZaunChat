#pragma once
#include"msghandler.h"

class LoginHandler :public MsgHandler {
	Q_OBJECT
public:
    explicit LoginHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
