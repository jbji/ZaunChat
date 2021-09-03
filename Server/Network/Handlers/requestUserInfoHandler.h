#pragma once
#include"msghandler.h"

class RequsetUserInfoHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit RequsetUserInfoHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
