#include "clientcontroller.h"

#include "Network/handlerreg.h"
#include "DataModel/Msg/msg.h"
#include "Network/ResAssist/downloader.h"
ClientController::ClientController(QObject* parent) : QObject(parent)
{
	//初始化 存储ID到聊天消息列表List映射的Map
	chatMsgMap = QMap<quint32, QList<ChatMessage>*>();
	friendList = QList<UserInfo>();

	chatMsgMapGroup = QMap<quint32, QList<GroupChatMessage>*>();
	groupList = QList<GroupInfo>();

    chatImg = QMap<QString, quint32>();
	//登录成功时 初始化聊天信息Map 以及获取好友列表
	connect((LoginHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::LOGIN_SUCCESS),
		&LoginHandler::sigLoginSuccessful,
		this,
		&ClientController::requestFriendList);
    connect((FriendListHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::ALL_FRIEND_LIST),
        &FriendListHandler::sigFriendListGotcha,
        this,
        &ClientController::requestGroupList);
	connect((FriendListHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::ALL_FRIEND_LIST),
		&FriendListHandler::sigFriendListGotcha,
		this,
		&ClientController::requestAllFriendListUserInfo);
	connect((FriendListHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::ALL_FRIEND_LIST),
		&FriendListHandler::sigFriendListGotcha,
		this,
		&ClientController::requestGroupList);

    connect((ChatMsgHandler *)HandlerReg::GetRegObj()->getHandler(MsgType::MSG_PIC)
            , &ChatMsgHandler::readyShowChatPic, Downloader::GetInstance(), &Downloader::bufferImg);

}

ClientController::~ClientController() {
	for (auto& x : chatMsgMap) {
		delete x;
	}
	for (auto* x : chatMsgMapGroup) {
		delete x;
	}
	friendList.clear();
	groupList.clear();
}


//实现客户端控制器的单例
ClientController* ClientController::obj = nullptr;


ClientController* ClientController::GetClientInstance() {
	if (!obj) {
		obj = new ClientController();
	}
	return obj;
}

QString ClientController::IP = "192.168.43.244";

//初始化客户端的Socket
TcpClientSocket* ClientController::socket = NULL;


TcpClientSocket* ClientController::GetSocket() {
	if (socket == NULL) {
		socket = new TcpClientSocket();
	}
	return socket;
}


void ClientController::ConnectToServer() {
	TcpClientSocket* clientSocket = GetSocket();
    clientSocket->setServerIP(IP);
	clientSocket->setServerTcpPort("9999");
	if (!clientSocket->connectToServer()) {
		qDebug() << "[connectToServer] Connection Failed.";
	}
	else {
		qDebug() << "[connectToServer] Connection Successful.";
	}
}
void ClientController::requestUserInfoByID(quint32 ID) {
	QByteArray content;
	content.clear();
	content.append(QString::number(ID));
	GetSocket()->sendMessage(new Msg(MsgType::REQUEST_USERINFO, content));
}


//debug
void ClientController::requestChatFile(ChatMessage chat_msg){
    ClientController::GetClientInstance()->requestFileByRawMsg(chat_msg);
}
