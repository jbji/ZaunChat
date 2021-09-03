#include"clientcontroller.h"
#include "Network/ResAssist/res.h"

#include <QFile>
#include <QFileInfo>

//换用户名
void ClientController::requestModifyUserName(QString newUserName) {
	UserInfo OldUserInfo = getMyInfo();
	GetSocket()->sendMessage(new Msg(MsgType::MODIFY_USERNAME,
        UserInfo(OldUserInfo.getID(), newUserName, OldUserInfo.getPwd(),
			OldUserInfo.getAvatarName()).toQByteArray()));
}


//请求更换头像, 返回头像的完整路径
QString ClientController::requestModifyAvatar(QString imgAbsolutePath){
    if(LocalCache::GetInstance()->isExistFileByAbsolutePath(imgAbsolutePath)){
        //作为资源上传的部分(会保存到本地)
        FileMeta file_info = FileMeta( getMyInfo(), QFileInfo(QFile(imgAbsolutePath)).fileName() );
        Uploader::GetInstance()->uploadImg(file_info, imgAbsolutePath);
        UserInfo me = getMyInfo();
        //必须服务端验证密码正确后才允许更改头像
        UserInfo new_me = UserInfo(me.getID(), me.getName(), me.getPwd(), file_info.getUniqueName());
        GetSocket()->sendMessage(new Msg(MsgType::MODIFY_AVATAR, new_me.toQByteArray()));
        return LocalCache::GetInstance()->getImgFullPath(file_info.getUniqueName());
    }
    return "";
}
