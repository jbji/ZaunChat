#include "serverhandlerreg.h"

QMap<MsgType, MsgHandler * > ServerHandlerReg::handler_regs;
ServerHandlerReg * ServerHandlerReg::regObj = nullptr;

ServerHandlerReg::ServerHandlerReg(QObject * parent):
    QObject(parent)
{
    initialize();
}

ServerHandlerReg * ServerHandlerReg::GetRegObj(){
    if(!regObj){
        regObj = new ServerHandlerReg();
    }
    return regObj;
}

MsgHandler * ServerHandlerReg::getHandler(MsgType type){
//    qDebug() << "Fetching Handler Type:" << QString::number(quint16(type));
    if(handler_regs.contains(type)){
        return handler_regs[type];
    }else{
        qDebug() << "未找到对应类型的handler! 请检查是否忘记注册消息类型";
    }
    return nullptr;
}

void ServerHandlerReg::regHandler(MsgType type, MsgHandler *msg_handler){
    handler_regs[type] = msg_handler;
}

void ServerHandlerReg::initialize(){
    MsgHandler * msghandler = new ChatMsgHandler(this);
    regHandler(MsgType::MSG_PLAIN_TEXT,msghandler);
    regHandler(MsgType::MSG_FILE, msghandler);
    regHandler(MsgType::MSG_PIC, msghandler);
    regHandler(MsgType::MSG_EMOTION, msghandler);
    regHandler(MsgType::MSG_WINDOW_SHAKE, msghandler);

    MsgHandler * loginhandler = new LoginHandler(this);
    regHandler(MsgType::REQUEST_LOGIN, loginhandler );

    MsgHandler * reghandler = new RegisterHandler(this);
    regHandler(MsgType::REQUEST_REGISTER, reghandler);

    MsgHandler * friendshiphandler = new FriendshipHandler(this);
    regHandler(MsgType::REQUEST_ADD_FRIEND, friendshiphandler);

    MsgHandler * requestallfriendlisthandler = new RequestAllFriendListHandler(this);
    regHandler(MsgType::REQUEST_ALL_FRIEND_LIST,requestallfriendlisthandler);

    MsgHandler * addfriendresulthandler = new AddFriendResultHandler(this);
    regHandler(MsgType::REQUEST_ADD_FRIEND_AGREED, addfriendresulthandler);
    regHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED, addfriendresulthandler);

    MsgHandler * logouthandler = new LogoutHandler(this);
    regHandler(MsgType::REQUEST_LOGOUT, logouthandler);

    MsgHandler * requestUserInfoHandler = new RequsetUserInfoHandler(this);
    regHandler(MsgType::REQUEST_USERINFO, requestUserInfoHandler);

    MsgHandler* offLineMsgHandler = new OffLineMsgHandler(this);
    regHandler(MsgType::REQUEST_OFFLINE_MSG, offLineMsgHandler);

    MsgHandler * registerGroupHandler = new RegisterGroupHandler(this);
    regHandler(MsgType::REQUEST_REGISTER_GROUP,registerGroupHandler);

    MsgHandler * modifyUsernameHandler = new ModifyUsernameHandler(this);
    regHandler(MsgType::MODIFY_USERNAME, modifyUsernameHandler);

    MsgHandler* modifyAvatarHandler = new ModifyAvatarHandler(this);
    regHandler(MsgType::MODIFY_AVATAR, modifyAvatarHandler);

    MsgHandler * addGroupHandler = new AddGroupHandler(this);
    regHandler(MsgType::REQUEST_ADD_GROUP, addGroupHandler);

    MsgHandler * requestAllGroupListHandler = new RequestAllGroupListHandler(this);
    regHandler(MsgType::REQUEST_ALL_GROUP_LIST, requestAllGroupListHandler);

    MsgHandler* groupMsgHandler = new GroupMsgHandler(this);
    regHandler(MsgType::GROUP_MSG_PLAIN_TEXT, groupMsgHandler);


}
