#ifndef HANDLERREG_H
#define HANDLERREG_H

#include <QObject>
#include <QMap>

#include "DataModel/datamodel.h"
#include "Network/Handlers/msghandler.h"
#include "Network/handlers.h"
#include "Network/Handlers/userinfo_handler.h"
#include "Network/Handlers/register_group_handler.h"
#include "Network/Handlers/modify_username_result_handler.h"
#include "Network/Handlers/group_add_request_result.h"
#include "Network/Handlers/grouplist_handler.h"
#include "Network/Handlers/group_msg_handler.h"

//用法举例: MsgHandler * h = HandlerReg::GetRegObj()->getHandler(MSG_PLAIN_TEXT);
class HandlerReg : public QObject
{
    Q_OBJECT
public:
    HandlerReg(QObject * parent = nullptr);

    //1.获得RegObj, 然后才可以使用getHandler
    static HandlerReg * GetRegObj();
    //2.从handler注册表中寻找MsgType对应的Handler, 在这里找到Handler之后, 再去把它和对应的Slot做Connect.
    MsgHandler * getHandler(MsgType);

protected:
    void initialize();

private:

    //注册一种handler的方法
    void regHandler( MsgType type, MsgHandler * msg_handler);

    //Handler注册表的Map
    static QMap<MsgType, MsgHandler * > handler_regs;
    //GetRegObj返回的对象
    static HandlerReg * regObj;

};

#endif // HANDLERREG_H
