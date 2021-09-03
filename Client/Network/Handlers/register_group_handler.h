#ifndef REGISTER_GROUP_HANDLER_H
#define REGISTER_GROUP_HANDLER_H
#include <QObject>

#include "msghandler.h"

class RegisterGroupHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit RegisterGroupHandler(QObject *parent = nullptr);

    void parse(Msg & );

signals:
    void sigRegGroupSuccessful(GroupInfo info);
    void sigRegGroupFailed();
    void refreshGroupList();

};

#endif // REGISTER_GROUP_HANDLER_H
