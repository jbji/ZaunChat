#include"group_add_request_result.h"
#include "DataModel/Msg/msgtype.h"
#include "Utilities/utilities.h"
#include"Controller/clientcontroller.h"

AddGroupResultHandler::AddGroupResultHandler(QObject* parent) : MsgHandler(parent) {

}

void AddGroupResultHandler::parse(Msg& msg) {
    GroupInfo newGroupInfo = GroupInfo::fromQByteArray(msg.getContent());
    if (msg.getType() == MsgType::ADD_GROUP_SUCCESS) {
        Log::GetLogObj()->writeLog("[AddGroupResult Handler] addgroup_successful");
        ClientController::GetClientInstance()->dynamicAppendGroup(newGroupInfo);
        emit sigAddGroupSuccessful(GroupInfo::fromQByteArray(msg.getContent()));
        emit refreshGroupList();
    }
    else{
        Log::GetLogObj()->writeLog("[AddGroupResult Handler] addgroup_fail");
        emit sigAddGroupFailed(msg.getType());
    }
}
