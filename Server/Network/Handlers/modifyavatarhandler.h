#ifndef MODIFYAVATARHANDLER_H
#define MODIFYAVATARHANDLER_H

#include "msghandler.h"
#include <QObject>

class ModifyAvatarHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit ModifyAvatarHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);

};

#endif // MODIFYAVATARHANDLER_H
