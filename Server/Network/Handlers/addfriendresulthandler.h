#ifndef ADDFRIENDRESULTHANDLER_H
#define ADDFRIENDRESULTHANDLER_H

#include "msghandler.h"
#include "Utilities/log.h"
#include "DataModel/Msg/msg.h"
#include "DataModel/Msg/msgtype.h"
#include "DataModel/chatmessage.h"
#include "DataBase/datadb.h"
#include "servercontroller.h"

class AddFriendResultHandler : public MsgHandler
{
    Q_OBJECT
public:
    AddFriendResultHandler(QObject* parent = nullptr);

    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};

#endif // ADDFRIENDRESULTHANDLER_H
