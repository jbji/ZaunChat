#pragma once
#include <QObject>

#include "msghandler.h"


//实际上不需要signal, 直接把读到的好友列表直接写到FriendList变量里即可

class GroupListHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit GroupListHandler(QObject* parent = nullptr);
    void parse(Msg&);
signals:
    void sigGroupListGotcha(UserInfo info);
};
