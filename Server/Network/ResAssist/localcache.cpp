#include "localcache.h"

#include <QFile>



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
    return QFile::exists(".//cache//files//"+file_unique_name);
}

bool LocalCache::isExistFile(FileMeta info){
    return QFile::exists(".//cache//files//"+info.getBaseName() + "_" + info.getUniqueName());
}

bool LocalCache::isExistImg(QString img_unique_name){
    return QFile::exists(".//cache//images//"+img_unique_name);
}

QString LocalCache::getFileFullPath(QString file_unique_name){
    return ".//caches//files//" + file_unique_name;
}

QString LocalCache::getImgFullPath(QString img_unique_name){
    return ".//caches//images//" + img_unique_name;
}

