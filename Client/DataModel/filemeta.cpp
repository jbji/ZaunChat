#include "filemeta.h"

#include "Utilities/utilities.h"


FileMeta::FileMeta(UserInfo user, QString original_name)
    :original_name(original_name)
{
    int dot_index = original_name.lastIndexOf(".");
    unique_name = StdDatetimeUtilities::GetDateTimeWithNoSpace()//时间和日期
            + QString::number(user.getID())//ID
            + original_name.mid(dot_index);//扩展名
}

QString FileMeta::toQString(){
    return QString( (unique_name + ":" + original_name).toUtf8().toBase64());
}

FileMeta FileMeta::fromQByteArray(QByteArray msg_content){
    QStringList meta_in = QString(QByteArray::fromBase64(msg_content, QByteArray::Base64Encoding)).split(":");
    FileMeta tmp;
    tmp.unique_name = meta_in[0];
    tmp.original_name = meta_in[1];
    return tmp;
}
