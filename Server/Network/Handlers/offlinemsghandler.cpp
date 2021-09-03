#include "offlinemsghandler.h"
#include "servercontroller.h"
#include <QString>
#include "Utilities/log.h"
#include "DataBase/datadb.h"

OffLineMsgHandler::OffLineMsgHandler(QObject* parent) :MsgHandler(parent) {

}

void OffLineMsgHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[OfflineMsg Handler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_OFFLINE_MSG) {
        Log::GetLogObj()->writeLog("[OfflineMsg Handler] Register Msg Error.");
        return;
    }
    quint32 id = msg.getContent().toUInt();
    DataDB* db = DataDB::GetInstance();
    QList<ChatMessage> list = db->getOfflineMsg(id);
    if (!list.isEmpty()) {
        for (auto& x : list) {
            Log::GetLogObj()->writeLog("["+x.getContent()+"]");
			socket->sendMessage(new Msg(MsgType::MSG_PLAIN_TEXT, x.toQByteArray()));
        }
        db->dropOfflineMsg(id);
    }
    else Log::GetLogObj()->writeLog("[OfflineMsg Handler] NO_OFFLINE_MSG");
    Log::GetLogObj()->writeLog("[Friendship Handler] ParseDone");
}
