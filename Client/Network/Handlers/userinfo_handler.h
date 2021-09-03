#ifndef USERINFO_HANDLER_H
#define USERINFO_HANDLER_H
#include <QObject>

#include "msghandler.h"

class UserInfoHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit UserInfoHandler(QObject *parent = nullptr);

    void parse(Msg & );

signals:
    void readyShowUserInfo(UserInfo info);
    void readyRefreshFriendList();
};
#endif // USERINFO_HANDLER_H
