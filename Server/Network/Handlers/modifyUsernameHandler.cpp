#include "modifyUsernameHandler.h"
#include "servercontroller.h"
#include <QString>
#include "Utilities/log.h"
#include "DataBase/datadb.h"

ModifyUsernameHandler::ModifyUsernameHandler(QObject* parent) :MsgHandler(parent) {

}

void ModifyUsernameHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[ModifyUsername Handler] Trying Parse");
    if (msg.getType() != MsgType::MODIFY_USERNAME) {
        Log::GetLogObj()->writeLog("[ModifyUsername Handler] Register Msg Error.");
        return;
    }
    //获取现在的信息
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    DataDB* db = DataDB::GetInstance();
    if(db->selectUserByIdAndPwd(tmp.getID(), tmp.getPwd())){
        db->updUsername(tmp.getID(),tmp.getName());
        socket->sendMessage(new Msg(MsgType::MODIFY_USERNAME_SUCCESS, tmp.toQByteArray()));
    }//可以加入else语句来说编辑失败
    Log::GetLogObj()->writeLog("[ModifyUsername Handler] ParseDone");
}
