#ifndef SERVERHANDLERREG_H
#define SERVERHANDLERREG_H

#include <QObject>
#include <QMap>

#include "DataModel/Msg/msgtype.h"
#include "Network/Handlers/msghandler.h"

#include "Network/Handlers/RegisterHandler.h"
#include "Network/Handlers/LoginHandler.h"
#include "Network/Handlers/chatmsghandler.h"
#include "Network/Handlers/FriendshipHandler.h"
#include "Network/Handlers/requestallfriendlisthandler.h"
#include "Network/Handlers/addfriendresulthandler.h"
#include "Network/Handlers/LogoutHandler.h"
#include "Network/Handlers/requestUserInfoHandler.h"
#include "Network/Handlers/offlinemsghandler.h"
#include "Network/Handlers/registerGroupHandler.h"
#include "Network/Handlers/modifyUsernameHandler.h"
#include "Network/Handlers/addGroupHandler.h"
#include "Network/Handlers/requestAllGroupListHandler.h"
#include "Network/Handlers/group_msg_handler.h"
#include "Network/Handlers/modifyavatarhandler.h"

class ServerHandlerReg:public QObject
{
    Q_OBJECT
public:
    ServerHandlerReg(QObject * parent = nullptr);

    static ServerHandlerReg * GetRegObj();
    MsgHandler * getHandler(MsgType);
protected:
    void initialize();
private:
    void regHandler(MsgType type, MsgHandler * msg_handler);

    static QMap<MsgType, MsgHandler *> handler_regs;
    static ServerHandlerReg * regObj;
};

#endif // SERVERHANDLERREG_H
