#pragma once
#include "msghandler.h"

class RegisterHandler :public MsgHandler {
	Q_OBJECT
public:
    explicit RegisterHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
