#include "Controller/clientcontroller.h"

#include "Network/ResAssist/res.h"

#include <QFile>
#include <QFileInfo>
#include <QScreen>
#include <QGuiApplication>
#include <QDir>
#include "Utilities/utilities.h"
#include <QPixmap>


//请求发送图片
bool ClientController::requestSendImg(quint32 receiver, QString imgAbsolutePath){
    //如果图片存在
    qDebug()<<"receiver:   " + QString::number(receiver);
    if(LocalCache::GetInstance()->isExistFileByAbsolutePath(imgAbsolutePath)){
        //作为资源上传的部分(会保存到本地)
        FileMeta file_info = FileMeta( getMyInfo(), QFileInfo(QFile(imgAbsolutePath)).fileName() );
        Uploader::GetInstance()->uploadImg(file_info, imgAbsolutePath, receiver);
        return true;
    }
    return false;
}
//请求发送文件
bool ClientController::requestSendFile(quint32 receiver, QString fileAbsolutePath){
    //如果文件存在
    if(LocalCache::GetInstance()->isExistFileByAbsolutePath(fileAbsolutePath)){
        //作为资源上传的部分(会保存到本地)
        FileMeta file_info = FileMeta( getMyInfo(), QFileInfo(QFile(fileAbsolutePath)).fileName() );
        Uploader::GetInstance()->uploadFile(file_info, fileAbsolutePath, receiver);
        return true;
    }
    return false;
}

QString ClientController::requestFullScreenShot(quint32 receiver) {
    QScreen* screen = QGuiApplication::primaryScreen();
    QDir* folder = new QDir;
    if (!folder->exists("./cache/screenshots")) {
        folder->mkpath("./cache/screenshots");
    }
    QString filePath = "./cache/screenshots/" + StdDatetimeUtilities::GetDateTimeWithNoSpace() + ".jpg";
    bool IsSuccess = true;
    IsSuccess &= screen->grabWindow(0).save(filePath, "jpg");
    IsSuccess &= requestSendImg(receiver, filePath);
    emit readyShowMyPIC(filePath,getMyInfo().getID());
    return IsSuccess ? filePath : "";
}

//请求下载文件
void ClientController::requestFileByRawMsg(ChatMessage msg){
    //获得要请求的文件的元信息
    FileMeta info_to_request = FileMeta::fromQByteArray(msg.getContent().toUtf8());
    Log::GetLogObj()->writeLog("[requestFileByRawMsg] 正在请求文件" + info_to_request.getBaseName());
    Downloader::GetInstance()->requestFileResource(info_to_request);
}
