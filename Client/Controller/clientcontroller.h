#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>

#include "DataModel/chatmessage.h"
#include "Network/tcpclientsocket.h"
#include "Utilities/utilities.h"
#include "DataModel/group_chat_message.h"
#include "GUI/mainwindow.h"

class ClientController : public QObject
{
	Q_OBJECT
public:
	explicit ClientController(QObject* parent = nullptr);
	~ClientController();

	//有关客户端自己
	static ClientController* GetClientInstance();

	UserInfo& getMyInfo();
	void requestUserInfoByID(quint32 ID);
	//**** 有关消息 xx_chat.cpp ****
	//发送消息的函数
	void sendChatMessage(ChatMessage& chat_msg);
	void sendChatMessage(quint32 receiver, QString content);
    void sendWindowShake(quint32 receiver); //窗口抖动
	//Group message
	void sendGroupChatMessage(quint32 groupId, QString content);

	//获取本地的聊天记录
	QList<ChatMessage>* getChatMsg(quint32 id);

	//请求发送图片/文件 成功返回true 失败返回false
	bool requestSendImg(quint32 receiver, QString imgAbsolutePath);
	bool requestSendFile(quint32 receiver, QString fileAbsolutePath);

    //返回本地截屏存放的路径
    QString requestFullScreenShot(quint32 receiver);

	//请求下载文件
	void requestFileByRawMsg(ChatMessage);

	//如果要显示来自readyShowChatFile的文件名,需要  FileMeta::FromQByteArray(xx.getContent()).getBaseName;


	//****有关登录注册  有关消息 xx_reg_login.cpp ****

	//登录 注册的请求 它们都会调用SafeUtilites::GetPasswordHash(password)去加密明文密码
	void requestLogin(quint32 id, QString password);
	void requestRegister(QString username, QString password);
	//下线请求
	void requestLogout(quint32 id);


	// **** 有关好友 xx_friend.cpp ****

	//好友相关
	void requestAddFriend(quint32 receiver, QString verifyMsg = "");
	void agreeFriendRequest(quint32 sender, quint32 receiver, QString s = "");
	void declineFriendRequest(quint32 sender, quint32 receiver, QString s = "");

	QList<UserInfo>* getFriendList(); //获得好友列表
	QList<GroupInfo>* getGroupList();//获得群聊列表

	//Modify-request
	void requestModifyUserName(QString newUserName);
    QString requestModifyAvatar(QString imgAbsolutePath); //输入是图像的原始路径, 返回头像的缓存路径

	// **** 有关群聊 xx_group.cpp ****
	void registerGroup(QString groupName);
	void requestAddGroup(quint32 id);

    //获得IP设置
    static QString GetServerIP(){return IP;}

	//友元
	friend class FriendListHandler;
	friend class ChatMsgHandler;
	friend class FriendRequestResultHandler;
	friend class GroupListHandler;
	friend class AddGroupResultHandler;
	friend class RegisterGroupHandler;
	friend class GroupMsgHandler;
	friend class UserInfoHandler;
    friend class MainWindow;
    friend class addfriendalert;
    QMap<QString, quint32> * GetChatImg(){return &chatImg;}
signals:
    void readyShowPIC(QString path, quint32 id);
    void readyShowMyPIC(QString path, quint32 id);
private slots:

	void requestFriendList(UserInfo info);

	void requestOfflineMsg();

	void requestAllFriendListUserInfo();

	void dynamicAppendFriend(UserInfo _friend); //动态append好友
	void dynamicAppendGroup(GroupInfo _group); //动态append group

	void requestGroupList();


    //debug
    void requestChatFile(ChatMessage chat_msg);

private:

	QMap<quint32, QList<ChatMessage>*>* getChatMsgMap() { return &chatMsgMap; }
	QMap<quint32, QList<ChatMessage>*> chatMsgMap;

	QList<UserInfo> friendList;

	QMap<quint32, UserInfo>& getIdToUserInfoMap() { return idToUserInfoMap; }
	QMap<quint32, UserInfo>  idToUserInfoMap;

	//群聊相关
	QMap<quint32, QList<GroupChatMessage>*>* getChatMsgMapGroup() { return &chatMsgMapGroup; }
	QMap<quint32, QList<GroupChatMessage>*> chatMsgMapGroup;

    QMap<QString, quint32> chatImg;
	QList<GroupInfo> groupList;

	static ClientController* obj; //自己的实例

	//ClientController负责托管Socket
    static QString IP;
	static void ConnectToServer();
	static TcpClientSocket* GetSocket();
	static TcpClientSocket* socket;
};

#endif // CLIENTCONTROLLER_H
