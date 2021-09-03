#include "downloader.h"
#include "Network/handlerreg.h"

#include "ressocket.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{

}


Downloader * Downloader::obj = nullptr;

Downloader * Downloader::GetInstance(){
    if(!obj) obj = new Downloader();
    return obj;
}


//主动请求文件资源
void Downloader::requestFileResource(FileMeta info){
    ResSocket::GetSocket()->sendMessage(new Msg(MsgType::RES_REQUEST_FILE, info.toQString().toUtf8()));
}

//自动请求图片资源
void Downloader::bufferImg(ChatMessage msg){
    FileMeta info_to_request = FileMeta::fromQByteArray(msg.getContent().toUtf8());
    ResSocket::GetSocket()->sendMessage(new Msg(MsgType::RES_REQUEST_IMG, info_to_request.toQString().toUtf8()));
}


//---以下功能未实现--
// 收到来自UserInfo信号readyShowUserInfo(UserInfo info) 开始触发, 获得单个好友的头像
void Downloader::bufferAvatar(UserInfo info){

} //多次获取单个用户的头像


