#pragma once
#include <QObject>

#include "msghandler.h"

class ModifyUserNameResultHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit ModifyUserNameResultHandler(QObject* parent = nullptr);

    void parse(Msg& msg);

signals:
    void modifyUserNameSuccess(QString newUserName);
    void modifyUserNameFail();

};