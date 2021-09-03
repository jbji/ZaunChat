#include "modifyavatarhandler.h"

#include "Utilities/utilities.h"
#include "DataModel/datamodel.h"
#include "DataBase/datadb.h"


ModifyAvatarHandler::ModifyAvatarHandler(QObject *parent) : MsgHandler(parent)
{

}

void ModifyAvatarHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[ModifyAvatar Handler] Trying Parse");
    if (msg.getType() != MsgType::MODIFY_AVATAR) {
        Log::GetLogObj()->writeLog("[[ModifyAvatar Handler] Msg Error.");
        return;
    }
    //验证密码是否一样 如果一样就更换头像.
    //获取现在的信息
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    DataDB* db = DataDB::GetInstance();
    if(db->selectUserByIdAndPwd(tmp.getID(), tmp.getPwd())){
        db->updAvatar(tmp.getID(),tmp.getAvatarName());
        //暂不返回成功或者失败
    }
    Log::GetLogObj()->writeLog("[ModifyAvatar Handler] ParseDone");
}
