#include "clientcontroller.h"
#include "Utilities/safeutilities.h"
#include "Network/handlerreg.h"

UserInfo& ClientController::getMyInfo(){
    LoginHandler * tmp = (LoginHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::LOGIN_SUCCESS);
    return tmp->getMyInfo();
}
//登录
void ClientController::requestLogin(quint32 id, QString password){

    password = SafeUtilities::GetPasswordHash(password);
    //密码做一次哈希

    UserInfo tmp(id, "", password);

    ConnectToServer();

    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_LOGIN,tmp.toQByteArray()));
}

//注册
void ClientController::requestRegister(QString username, QString password){

    password = SafeUtilities::GetPasswordHash(password);
    //密码做一次哈希

    UserInfo tmp = UserInfo(0x0000, username, password);

    ConnectToServer();

    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_REGISTER,tmp.toQByteArray()));
}

//登出
void ClientController::requestLogout(quint32 id) {
    UserInfo tmp(id, "","");
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_LOGOUT,tmp.toQByteArray()));
//    GetSocket()->close();
}

