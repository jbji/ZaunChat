#ifndef FRIEND_REQUEST_HANDLER_H
#define FRIEND_REQUEST_HANDLER_H
#include <QObject>

#include "msghandler.h"

class FriendRequestHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit FriendRequestHandler(QObject *parent = nullptr);

    void parse(Msg & msg);

signals:
    void readyShowFriendRequest(UserInfo sender);

};
#endif // FRIEND_REQUEST_HANDLER_H
