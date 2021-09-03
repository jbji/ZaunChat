#ifndef REGISTER_HANDLER_H
#define REGISTER_HANDLER_H

#include <QObject>

#include "msghandler.h"

class RegisterHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit RegisterHandler(QObject *parent = nullptr);

    void parse(Msg & );

signals:
    void sigRegSuccessful(UserInfo info);
    void sigRegFailed();

};

#endif // REGISTER_HANDLER_H
