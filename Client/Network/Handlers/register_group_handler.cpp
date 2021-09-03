#include "register_group_handler.h"
#include <QDebug>

#include "Utilities/log.h"
#include"Controller/clientcontroller.h"
RegisterGroupHandler::RegisterGroupHandler(QObject *parent) : MsgHandler(parent)
{
}

void RegisterGroupHandler::parse(Msg & msg){
    //不光要返回是否注册成功 还要返回账号信息
    MsgType registerStatus = msg.getType();

    if(registerStatus == MsgType::REGISTER_GROUP_SUCCESS){
        Log::GetLogObj()->writeLog("[ClientRegisterGropuHandler] 注册成功 ID:"+
                                   QString::number((GroupInfo::fromQByteArray(msg.getContent())).getID()));
        ClientController::GetClientInstance()->dynamicAppendGroup(GroupInfo::fromQByteArray(msg.getContent()));
        emit sigRegGroupSuccessful(GroupInfo::fromQByteArray(msg.getContent()));
        emit refreshGroupList();
    }else{
        emit sigRegGroupFailed();
        Log::GetLogObj()->writeLog("[ClientRegisterGropuHandler] 注册失败");
    }
}
