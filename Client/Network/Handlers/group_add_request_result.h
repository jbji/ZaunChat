#ifndef GROUP_ADD_REQUEST_RESULT_H
#define GROUP_ADD_REQUEST_RESULT_H
#include <QObject>

#include "msghandler.h"

class AddGroupResultHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit AddGroupResultHandler(QObject *parent = nullptr);

    void parse(Msg & );

signals:
    void sigAddGroupSuccessful(GroupInfo info);
    void sigAddGroupFailed(MsgType type);
    void refreshGroupList();;

};
#endif // GROUP_ADD_REQUEST_RESULT_H
