#include "localcache.h"

#include <QFile>

#include "Utilities/utilities.h"

LocalCache::LocalCache(QObject *parent) : QObject(parent)
{

}

LocalCache * LocalCache::obj = nullptr;
LocalCache * LocalCache::GetInstance(){
    if(!obj){
        obj = new LocalCache();
    }
    return obj;
}

bool LocalCache::isExistFileByAbsolutePath(QString absolutePath){
    return QFile::exists(absolutePath);
}

bool LocalCache::isExistFile(QString file_unique_name){
    return QFile::exists("./cache/files/"+file_unique_name);
}

bool LocalCache::isExistFile(FileMeta info){
    return QFile::exists(".//cache//files//"+info.getBaseName() + "_" + info.getUniqueName());
}

bool LocalCache::isExistImg(QString img_unique_name){
    return QFile::exists("./cache/images/"+img_unique_name);
}

QString LocalCache::getFileFullPath(QString file_unique_name){
    return "./cache/files/" + file_unique_name;
}

QString LocalCache::getImgFullPath(QString img_unique_name){
    return "./cache/images/" + img_unique_name;
}

void LocalCache::broadcastReceivedRes(MsgType type, FileMeta meta){
    qDebug()<<"broadcastReceivedRes" <<" "<<int(MsgType::RES_IMG) <<" "<<int(type);
    if(type == MsgType::RES_FILE) emit alreadyReceivedFile(meta);
    if(type == MsgType::RES_IMG) emit alreadyReceivedImg(LocalCache::getImgFullPath(meta.getUniqueName()), meta);
}
