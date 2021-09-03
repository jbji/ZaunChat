#ifndef CHATMSGHANDLER_H
#define CHATMSGHANDLER_H

#include "msghandler.h"
#include"DataModel/chatmessage.h"

class ChatMsgHandler: public MsgHandler
{
    Q_OBJECT
public:
    explicit ChatMsgHandler(QObject* parent = nullptr);
    void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // CHATMSGHANDLER_H
