#include "qbytearraylistutility.h"

#include <QtNetwork>

QByteArrayListUtility::QByteArrayListUtility()
{

}


QList<QByteArray> QByteArrayListUtility::fromQByteArray(QByteArray block){
    QDataStream in(block);
    in.setVersion(QDataStream::Qt_5_12);

    QList<QByteArray> tmp;

    quint32 item_count;
    in >> item_count;
    tmp.reserve(item_count);
    //Read and Write
    for(quint32 i = 0; i< item_count; i++){
        quint32 size;
        in >> size;
        tmp.push_back(QByteArray());
        tmp[i].resize(size);
        in >> tmp[i];
    }

    return tmp;
}

// |quint32 item_count |quint32 size| QByteArray | ...

QByteArray QByteArrayListUtility::toQByteArray(QList<QByteArray> list){

    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    //输出
    quint32 item_count = list.length();
    out << quint32(item_count);
    for(quint32 i = 0; i < item_count; i++){
        int size_index = block.size();
        out << quint32(0);
        out << list[i];
        out.device()->seek(size_index);
        out << (quint32)(block.size() - size_index - sizeof(quint32));
        out.device()->seek(block.size());
    }



    return block;

}
