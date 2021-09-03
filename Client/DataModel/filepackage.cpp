#include "filepackage.h"

#include <QtNetwork>

QByteArray FilePackage::toQByteArray(){

    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    int size_index = block.size();
    out << quint32(0);
    out << info.toQString();
    out.device()->seek(size_index);
    out << (quint32)(block.size() - size_index - sizeof(quint32));
    out.device()->seek(block.size());

    size_index = block.size();
    out << quint32(0);
    out << content;
    out.device()->seek(size_index);
    out << (quint32)(block.size() - size_index - sizeof(quint32));
    out.device()->seek(block.size());

    out << quint32(sender);
    out << quint32(receiver);

    return block;

}
FilePackage FilePackage::fromQByteArray(QByteArray data){
    QDataStream in(data);
    in.setVersion(QDataStream::Qt_5_12);
    FilePackage tmp_file;

    quint32 size;
    in >> size;
    QByteArray tmpMeta;
    tmpMeta.resize(size);
    in >> tmpMeta;
    tmp_file.info = FileMeta::fromQByteArray(tmpMeta);

    in >> size;
    QByteArray tmpContent;
    tmpContent.resize(size);
    in >> tmpContent;
    tmp_file.content = tmpContent;

    quint32 tmp;
    in >> tmp;
    tmp_file.sender = tmp;
    in >> tmp;
    tmp_file.receiver = tmp;

    return tmp_file;
}
