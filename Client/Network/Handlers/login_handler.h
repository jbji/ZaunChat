#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include <QObject>

#include "msghandler.h"

class LoginHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit LoginHandler(QObject *parent = nullptr);

    void parse(Msg & );

	UserInfo& getMyInfo();

signals:
    void sigLoginFailed();
    void sigLoginSuccessful(UserInfo info);

private:
    UserInfo myInfo; // LoginHandler特有, 请勿复制.
};

#endif // LOGIN_HANDLER_H
