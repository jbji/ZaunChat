#include"modify_username_result_handler.h"
#include "DataModel/Msg/msgtype.h"
#include "Utilities/utilities.h"
#include"Controller/clientcontroller.h"

ModifyUserNameResultHandler::ModifyUserNameResultHandler(QObject* parent) : MsgHandler(parent) {

}

void ModifyUserNameResultHandler::parse(Msg& msg) {
	Log::GetLogObj()->writeLog("[ModifyUserNameResultHandler] Received_modify_result tring parse");
	UserInfo newUserInfo = UserInfo::fromQByteArray(msg.getContent());
	if (msg.getType() == MsgType::MODIFY_USERNAME_SUCCESS) {
		Log::GetLogObj()->writeLog("[ModifyUserNameResultHandler] modify_success");
		ClientController* cc = ClientController::GetClientInstance();
		UserInfo& myInfo = cc->getMyInfo();
		myInfo = UserInfo(myInfo.getID(), newUserInfo.getName(), myInfo.getPwd(), myInfo.getAvatarName());
		emit modifyUserNameSuccess(newUserInfo.getName());
	}
	else if (msg.getType() == MsgType::MODIFY_USERNAME_ERROR) {
		Log::GetLogObj()->writeLog("[ModifyUserNameResultHandler] modify_fail");
		emit modifyUserNameFail();
	}
	else {
		Log::GetLogObj()->writeLog("[ModifyUserNameResultHandler] received_wrong_msgtype");
	}
}
