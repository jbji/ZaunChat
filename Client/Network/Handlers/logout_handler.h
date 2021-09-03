#ifndef LOGOUT_HANDLER_H
#define LOGOUT_HANDLER_H

#include <QObject>

#include "msghandler.h"

class LogoutHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit LogoutHandler(QObject *parent = nullptr);

    void parse(Msg & );

    UserInfo getMyInfo();

signals:
    void sigLogoutFailed();
    void sigLogoutSuccessful(UserInfo info);

};
#endif // LOGOUT_HANDLER_H
