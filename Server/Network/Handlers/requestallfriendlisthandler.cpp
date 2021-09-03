#include"requestallfriendlisthandler.h"
#include"Utilities/log.h"
#include"DataBase/datadb.h"
#include"Utilities/qbytearraylistutility.h"

RequestAllFriendListHandler::RequestAllFriendListHandler(QObject* parent) : MsgHandler(parent) {

}

void RequestAllFriendListHandler::parse(Msg& msg, TcpClientSocket* socket) {
	Log::GetLogObj()->writeLog("[RequestAllFriendList Handler] Trying Parse");
	if (msg.getType() != MsgType::REQUEST_ALL_FRIEND_LIST) {
		Log::GetLogObj()->writeLog("[RequestAllFriendList Handler] Request all friend list Msg Error.");
		return;
	}
	quint32 id = msg.getContent().toUInt();
	DataDB* db = DataDB::GetInstance();
	QList<QByteArray> list = db->selectAllFriendsUserInfo(id);
	QByteArray content = QByteArrayListUtility::toQByteArray(list);
	Log::GetLogObj()->writeLog("[RequestAllFriendListHandler] ParseDone");
    socket->sendMessage(new Msg(MsgType::ALL_FRIEND_LIST, content));
}
