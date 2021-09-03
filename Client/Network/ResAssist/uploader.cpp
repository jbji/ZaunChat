#include "uploader.h"

#include "ressocket.h"

#include "DataModel/datamodel.h"
#include "Utilities/log.h"
#include "QFile"
#include "QDir"
#include "Controller/clientcontroller.h"

Uploader::Uploader(QObject *parent) : QObject(parent)
{

}


Uploader * Uploader::obj = nullptr;

Uploader * Uploader::GetInstance(){
    if(!obj) obj = new Uploader();
    return obj;
}

void Uploader::uploadImg(FileMeta filemeta, QString absolutePath, quint32 receiver){
    QFile file(absolutePath);
    file.open(QIODevice::ReadOnly);
    QByteArray block = file.readAll();
    file.close();
    //在上传之前先把图片保存到本地.
    QDir *folder = new QDir;
    if(!folder->exists("./cache/images")){
        folder->mkpath("./cache/images");
    }
    QFile file_local("./cache/images/" + filemeta.getUniqueName());
    if(file_local.open(QIODevice::WriteOnly)){
        file_local.write(block);
        file_local.close();
    }
    //上传文件
    FilePackage pack = FilePackage(filemeta, block);
    pack.setTransferInfo(ClientController::GetClientInstance()->getMyInfo().getID(), receiver);
    Msg tmp = Msg(MsgType::RES_IMG, pack.toQByteArray());
    ResSocket::GetSocket()->sendMessage(&tmp);
}

void Uploader::uploadImg(FileMeta filemeta, QString absolutePath){
    QFile file(absolutePath);
    file.open(QIODevice::ReadOnly);
    QByteArray block = file.readAll();
    file.close();
    //在上传之前先把图片保存到本地.
    QDir *folder = new QDir;
    if(!folder->exists("./cache/images")){
        folder->mkpath("./cache/images");
    }
    QFile file_local("./cache/images/" + filemeta.getUniqueName());
    if(file_local.open(QIODevice::WriteOnly)){
        file_local.write(block);
        file_local.close();
    }
    //上传文件
    Msg tmp = Msg(MsgType::RES_IMG, FilePackage(filemeta, block).toQByteArray());
    ResSocket::GetSocket()->sendMessage(&tmp);
}

void Uploader::uploadFile(FileMeta filemeta, QString absolutePath){
    QFile file(absolutePath);
    file.open(QIODevice::ReadOnly);
    QByteArray block = file.readAll();
    file.close();
    //文件不用保存到本地
    //上传文件
    Msg tmp = Msg(MsgType::RES_FILE, FilePackage(filemeta, block).toQByteArray());
    ResSocket::GetSocket()->sendMessage(&tmp);
}

void Uploader::uploadFile(FileMeta filemeta, QString absolutePath, quint32 receiver){
    QFile file(absolutePath);
    file.open(QIODevice::ReadOnly);
    QByteArray block = file.readAll();
    file.close();
    //文件不用保存到本地
    //上传文件 包含转发信息
    FilePackage pack = FilePackage(filemeta, block);
    pack.setTransferInfo(ClientController::GetClientInstance()->getMyInfo().getID(), receiver);
    Log::GetLogObj()->writeLog("LocalFileTransferInfo:" + QString::number(pack.getSender()) + QString::number(pack.getReceiver()));
    Msg tmp = Msg(MsgType::RES_FILE, pack.toQByteArray());
    ResSocket::GetSocket()->sendMessage(&tmp);
}
