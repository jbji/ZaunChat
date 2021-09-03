#include "widget.h"
#include "ui_widget.h"

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include "Network/ResAssist/res.h"
#include "new_windows.h"

Widget::Widget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);


	//获得日志并写入
	connect(Log::GetLogObj(), &Log::readyShowLog, this, &Widget::showLog);
	//自动滚动日志区域
	connect(ui->recvMsgtextBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));

	connect((RegisterHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::REGISTER_SUCCESS),
		&RegisterHandler::sigRegSuccessful,
		this,
		&Widget::showRegisterSuccessful
	);

	connect((RegisterHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::REGISTER_ERROR),
		&RegisterHandler::sigRegFailed,
		this,
		&Widget::showRegisterFailed
	);

	connect((LoginHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::LOGIN_SUCCESS),
		&LoginHandler::sigLoginSuccessful,
		this,
		&Widget::showLoginSuccessful
	);

	connect((LoginHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::LOGIN_ERROR),
		&LoginHandler::sigLoginFailed,
		this,
		&Widget::showLoginFailed
	);

	connect((ChatMsgHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::MSG_PLAIN_TEXT),
		&ChatMsgHandler::readyShowChatMsg,
		this,
		&Widget::showChatMessage
	);

    connect((ChatMsgHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::MSG_FILE),
        &ChatMsgHandler::readyShowChatFile,
        this,
        &Widget::requestChatFile
    );


	connect((FriendRequestHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::REQUEST_ADD_FRIEND),
		&FriendRequestHandler::readyShowFriendRequest,
		this,
		&Widget::showFriendRequest);

	connect((FriendRequestResultHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED),
		&FriendRequestResultHandler::sigAddFriendFailed,
		this,
		&Widget::showAddFriendFailed
	);

	connect((FriendRequestResultHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
		&FriendRequestResultHandler::sigAddFriendSuccessful,
		this,
		&Widget::showAddFriendSuccessful
	);
	connect((RegisterGroupHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::REGISTER_GROUP_SUCCESS),
		&RegisterGroupHandler::sigRegGroupSuccessful,
		this,
		&Widget::showRegisterGroupSuccessful);
	connect((RegisterGroupHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::REGISTER_GROUP_ERROR),
		&RegisterGroupHandler::sigRegGroupFailed,
		this,
		&Widget::showRegisterGroupFailed);
	connect((ModifyUserNameResultHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::MODIFY_USERNAME_SUCCESS),
		&ModifyUserNameResultHandler::modifyUserNameSuccess,
		this,
		&Widget::showModifyUsernameSuccess);
	connect((AddGroupResultHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::ADD_GROUP_SUCCESS),
		&AddGroupResultHandler::sigAddGroupSuccessful,
		this,
		&Widget::showAddGroupSuccess);
	connect((AddGroupResultHandler*)HandlerReg::GetRegObj()->
		getHandler(MsgType::ADD_GROUP_ERROR),
		&AddGroupResultHandler::sigAddGroupFailed,
		this,
		&Widget::showAddGroupFailed);

    connect(LocalCache().GetInstance(), &LocalCache::alreadyReceivedFile,
            this, &Widget::showReceivedFile);

    connect(LocalCache().GetInstance(), &LocalCache::alreadyReceivedImg,
            this, &Widget::showReceivedImg);

    connect((GroupMsgHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::GROUP_MSG_PLAIN_TEXT),
            &GroupMsgHandler::groupMsgReceiveSuccess,
            this,
            &Widget::showGroupChatMessage);

//    QString path = "C://Windows//Web//4K//Wallpaper//Windows//img0_3840x2160.jpg";
//    if(LocalCache::GetInstance()->isExistFileByAbsolutePath(path)){
//        Uploader::GetInstance()->uploadFile(FileMeta(ClientController::GetClientInstance()->getMyInfo(),
//                                                     "img0_3840x2160.jpg"),
//                                            path);
//    }
	/*//debug专用区
	connect((UserInfoHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::USERINFO),
			&UserInfoHandler::readyShowUserInfo,
			this,
			&Widget::showUserInfo);
	//
	*/
}

Widget::~Widget()
{
	delete ui;
}


void Widget::on_login_button_clicked()
{
	quint32 id = ui->login_id->text().toUInt();
	QString pw = ui->login_pw->text();
	ClientController::GetClientInstance()
		->requestLogin(id, pw);
}

void Widget::on_register_button_clicked()
{
	qDebug() << "Clicking Register Button";
	QString username = ui->reg_name->text();
	QString pw = ui->reg_pw->text();
	ClientController::GetClientInstance()
		->requestRegister(username, pw);
}


//日志小窗口的槽函数
void Widget::showLog(QString str) {
	ui->recvMsgtextBrowser->append(str);
}

void Widget::autoScroll() {
	QTextCursor cursor = ui->recvMsgtextBrowser->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->recvMsgtextBrowser->setTextCursor(cursor);
}


//接收注册登录的槽函数
void Widget::showRegisterSuccessful(UserInfo info) {
	QString caption = "注册成功";
	ui->status->setText(caption);
	QString tmp = caption + "! \n您的账号是 " +
		QString::number(info.getID()) +
		"\n请牢记此账号用于登录.";
	QMessageBox::warning(NULL, caption, tmp);
}

void Widget::showRegisterFailed() {
	QString caption = "注册失败";
	ui->status->setText(caption);
	QString tmp = caption + "! "
		"\n您的用户名或者密码可能不符合要求.";
	QMessageBox::warning(NULL, caption, tmp);
}

//接受注册群聊的槽函数
void Widget::showRegisterGroupSuccessful(GroupInfo info) {
	QString caption = "注册成功";
	ui->status->setText(caption);
	QString tmp = caption + "! \n群聊ID是 " +
		QString::number(info.getID()) +
		"\n请牢记此账号用于加入群聊.";
	QMessageBox::warning(NULL, caption, tmp);
}

void Widget::showRegisterGroupFailed() {
	QString caption = "注册失败";
	ui->status->setText(caption);
	QString tmp = caption + "! "
		"\n您的用户名可能不符合要求.";
	QMessageBox::warning(NULL, caption, tmp);
}



void Widget::showLoginSuccessful(UserInfo info) {
	QString caption = "登录成功";
	ui->status->setText(caption);
	QString tmp = caption + "! \n欢迎您! " +
		info.getName() +
		"";
	ui->info_id->setText(QString::number(info.getID()));
	ui->info_pw->setText(info.getPwd());
	ui->info_name->setText(info.getName());
	QMessageBox::warning(NULL, caption, tmp);
}

void Widget::showLoginFailed() {
	QString caption = "登录失败";
	ui->status->setText(caption);
	QString tmp = caption + "! "
		"\n账号或密码输入错误.";
	QMessageBox::warning(NULL, caption, tmp);
}

void Widget::on_pushButton_clicked()
{
    ClientController::GetClientInstance()->sendChatMessage(ui->sendMsg_recvID->text().toUInt(),
        ui->MsgContentplainTextEdit->document()->toPlainText());
//    ClientController::GetClientInstance()->sendWindowShake(123);
}

void Widget::showChatMessage(ChatMessage msg) {
	Log::GetLogObj()->writeLog("[" + QString::number(msg.getSender()) + "] 对你说 : " + msg.getContent());
}

void Widget::on_pushButton_2_clicked() { //请求添加好友
	QString receiver_ = ui->reg_friendId->text();
	Log::GetLogObj()->writeLog("[" + QString::number(ClientController::GetClientInstance()->getMyInfo().getID()) + "]" + "want to add" + "[" + receiver_ + "]");
	ClientController::GetClientInstance()->requestAddFriend(receiver_.toUInt(), "");
}

void Widget::showAddFriendFailed(MsgType type) {
	Log::GetLogObj()->writeLog("[添加好友失败] 错误信息:" + QString::number((int)type));
}
void Widget::showAddFriendSuccessful() {
	Log::GetLogObj()->writeLog("[添加好友成功]");
}

void Widget::showFriendRequest(UserInfo cmsg) {
    Log::GetLogObj()->writeLog("[" + QString::number(cmsg.getID()) + "]" + "想添加你为好友!");
	new_win = new new_windows();
    new_win->SetSend(cmsg.getID());
    new_win->SetReceive(ClientController::GetClientInstance()->getMyInfo().getID());
	new_win->show();
	Log::GetLogObj()->writeLog("[Widget::showFriendRequest] TRING_show_newwindow");
}


void Widget::on_pushButton_4_clicked()//下线按钮
{
	ClientController::GetClientInstance()->
		requestLogout(
			ClientController::GetClientInstance()->getMyInfo().getID()
		);
}


void Widget::on_pushButton_3_clicked()//获取好友列表按钮
{
	Log::GetLogObj()->writeLog("[" + QString::number(ClientController::GetClientInstance()->getMyInfo().getID()) + "]'s Friends are:");
	auto i = ClientController::GetClientInstance()->getFriendList();
	QString list;
	for (auto& j : *i) {
		list.append("\n" + QString::number(j.getID()));
	}
	Log::GetLogObj()->writeLog(list);
}


void Widget::showUserInfo(UserInfo info) {
	Log::GetLogObj()->writeLog("[" + QString::number(info.getID()) + "," + info.getName() + "]");
}


void Widget::on_pushButton_5_clicked()
{
	ClientController* client = ClientController::GetClientInstance();
	client->registerGroup(ui->lineEdit_2->text());
}


void Widget::on_pushButton_6_clicked()
{
	ClientController* client = ClientController::GetClientInstance();
	client->requestAddGroup(ui->lineEdit_3->text().toUInt());
}
void Widget::showModifyUsernameSuccess(QString newUsername) {
	QString caption = "修改成功";
	ui->status->setText(caption);
	QString tmp = caption + "! "
		"\n您的新名字是:" + newUsername;
	QMessageBox::warning(NULL, caption, tmp);
}

void Widget::on_pushButton_7_clicked()
{
	ClientController* client = ClientController::GetClientInstance();
	client->requestModifyUserName(ui->lineEdit_4->text());
}
void Widget::showAddGroupSuccess(GroupInfo info) {
	QString caption = "添加成功";
	ui->status->setText(caption);
	QString tmp = caption + "! "
		"\n您已加入:" + info.getName();
	QMessageBox::warning(NULL, caption, tmp);
}
void Widget::showAddGroupFailed(MsgType type) {
	Log::GetLogObj()->writeLog("[添加群聊失败] 错误信息:" + QString::number((int)type));
}

void Widget::on_pushButton_8_clicked()
{
	Log::GetLogObj()->writeLog("[" + QString::number(ClientController::GetClientInstance()->getMyInfo().getID()) + "]'s Groups are:");
	auto i = ClientController::GetClientInstance()->getGroupList();
	QString list;
	for (auto& j : *i) {
		list.append("\n" + QString::number(j.getID()));
	}
	Log::GetLogObj()->writeLog(list);
}


void Widget::requestChatFile(ChatMessage msg){
    Log::GetLogObj()->writeLog("[ChatFile] 接收到文件, 尝试请求文件");
    ClientController::GetClientInstance()->requestFileByRawMsg(msg);
}

void Widget::on_pushButton_9_clicked()//测试发送图片
{
    quint32 receiver = ui->lineEdit_6->text().toUInt();
    QString path = ui->lineEdit_5->text();
    if(ClientController::GetClientInstance()->requestSendImg(receiver, path)){
        Log::GetLogObj()->writeLog("[requestSendImg] Success");
    }else{
        Log::GetLogObj()->writeLog("[requestSendImg] ERROR");
    }
}

void Widget::on_pushButton_10_clicked()//测试发送文件
{
    quint32 receiver = ui->lineEdit_6->text().toUInt();
    QString path = ui->lineEdit_5->text();
    if(ClientController::GetClientInstance()->requestSendFile(receiver, path)){
        Log::GetLogObj()->writeLog("[requestSendFile] Success");
    }else{
        Log::GetLogObj()->writeLog("[requestSendFile] ERROR");
    }

}

void Widget::showReceivedFile(FileMeta info){
    Log::GetLogObj()->writeLog("[ShowReceivedFile] 文件缓存成功, 文件信息:\n原始名称:" + info.getBaseName()
                               + "\n唯一名称(实际文件名):" + info.getUniqueName()
                               + "\n已保存至:" + LocalCache::GetInstance()->getFileFullPath(info.getUniqueName()) );
}

void Widget::showReceivedImg(QString path, FileMeta info){
    Log::GetLogObj()->writeLog("[ShowReceivedImg] 图片缓存成功, 图片信息:\n原始名称:" + info.getBaseName()
                               + "\n唯一名称(实际文件名):" + info.getUniqueName()
                               + "\n已保存至:" + LocalCache::GetInstance()->getImgFullPath(info.getUniqueName()) );
}



void Widget::on_pushButton_11_clicked()
{
    ClientController::GetClientInstance()->sendGroupChatMessage(ui->lineEdit_7->text().toUInt(),ui->MsgContentplainTextEdit->document()->toPlainText());
}

void Widget::showGroupChatMessage(GroupChatMessage msg) {
    Log::GetLogObj()->writeLog("[" + QString::number(msg.getUserInfo().getID()) + "] 对你说 : " + msg.getChatMessage().getContent());
}

void Widget::on_pushButton_12_clicked()
{
    quint32 receiver = ui->lineEdit_8->text().toUInt();
    ClientController::GetClientInstance()->requestFullScreenShot(receiver);
}

