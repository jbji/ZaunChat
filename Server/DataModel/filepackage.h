#ifndef FILEPACKAGE_H
#define FILEPACKAGE_H

#include "filemeta.h"

class FilePackage
{
public:
    explicit FilePackage() = default;
    FilePackage(const FileMeta & info, const QByteArray & content):info(info),content(content), sender(0), receiver(0){}

    QByteArray toQByteArray();
    static FilePackage fromQByteArray(QByteArray data);

    FileMeta & getInfo(){ return info; }
    QByteArray & getContent(){ return content; }
    quint32 getSender(){return sender;}
    quint32 getReceiver(){return receiver;}
    void setTransferInfo(quint32 _sender, quint32 _receiver){sender = _sender; receiver = _receiver;}

private:
    FileMeta info;
    QByteArray content;
    quint32 sender;
    quint32 receiver;
};

#endif // FILEPACKAGE_H
