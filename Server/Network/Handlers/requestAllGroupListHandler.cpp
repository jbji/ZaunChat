#include"requestAllGroupListHandler.h"
#include"Utilities/log.h"
#include"DataBase/datadb.h"
#include"Utilities/qbytearraylistutility.h"

RequestAllGroupListHandler::RequestAllGroupListHandler(QObject* parent) : MsgHandler(parent) {

}

void RequestAllGroupListHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[RequestAllGroupList Handler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_ALL_GROUP_LIST) {
        Log::GetLogObj()->writeLog("[RequestAllGroupList Handler] Request all friend list Msg Error.");
        return;
    }
    quint32 id = msg.getContent().toUInt();
    DataDB* db = DataDB::GetInstance();
    QList<QByteArray> list = db->selectAllGroupInfo(id);
    QByteArray content = QByteArrayListUtility::toQByteArray(list);
    Log::GetLogObj()->writeLog("[RequestAllGroupList] ParseDone");
    socket->sendMessage(new Msg(MsgType::ALL_GROUP_LIST, content));
}
