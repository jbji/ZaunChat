#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

#include "DataModel/datamodel.h"

//角色是Request的发送者
//这个类的作用有两个, 缓存图片资源、下载特定文件

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    static Downloader * GetInstance();

    // 手动获得聊天文件, 在ClientController的requestFileByRawMsg(ChatMessage)中触发
    void requestFileResource(FileMeta info);

signals:

    //void readyRefreshUserInfo(); //获取完用户信息了
    //void readyRefreshFiles();

public slots:

    // 自动获得聊天图片, 收到 readyShowChatPic时触发
    void bufferImg(ChatMessage msg); //获得单次聊天的图片

    //缓存文件和下载资源

    // 收到信号sigFriendListGotcha时Controller触发 requestOfflineMessage, 能不能再触发一个requestFullUserInfo
    // requestOfflineMsg -> requestOfflineMsg_FullUserInfo
    //readyShowUserInfo里会不会将完整的用户信息写入到friendList?

    // 收到来自UserInfo信号readyShowUserInfo(UserInfo info) 开始触发, 获得单个好友的头像
    void bufferAvatar(UserInfo info); //多次获取单个用户的头像



private:

    //你要通过这个Downloader, 给服务端发Request, 然后处理接收文件的Handler把文件存起来?

    void bufferImgResource(QString imgName); //buffer的具体实现形式


    static Downloader * obj;
};

#endif // DOWNLOADER_H
