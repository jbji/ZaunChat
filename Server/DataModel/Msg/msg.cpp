#include "msg.h"

#include <QtNetwork>


quint32 Msg::msgHead = 0xAC114514; //19260817 19530615

Msg::Msg(MsgType type, const QByteArray & content){
    this->type = type;
    this->content = content;
}


MsgType Msg::getType(){
    return type;
}

QByteArray & Msg::getContent(){
    return content;
}

//转换成可以直接发送的QByteArray数组
QByteArray Msg::toQByteArray(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << quint32(0);
    out << quint32(msgHead);
    out << quint16(type);
    out << content;
    out.device()->seek(0);
    out << (quint32)(block.size()-sizeof(quint32));
    return block;
}

//不包含开头8个字节, 将QByteArray转换成Msg对象

Msg Msg::fromQByteArray(const QByteArray & type_and_content){
    QDataStream in(type_and_content);
    in.setVersion(QDataStream::Qt_5_12);
    //将数据从type_and_content中拿出来
    quint16 tmp_type;
    QByteArray content;
    in >> tmp_type;
    in >> content;
    return Msg( (MsgType)(tmp_type), content );
}

//包含开头8个字节, 将QByteArray转换成Msg对象
Msg Msg::fromFullQByteArray(const QByteArray & full_received){
    QDataStream in(full_received);
    in.setVersion(QDataStream::Qt_5_12);
    //将数据从type_and_content中拿出来
    quint32 dataSize;
    in >> dataSize;
    //假如数据不完整, 停止读取
    if(full_received.size() - sizeof(quint32) < dataSize){
        return Msg( MsgType::UNDEFINED, QByteArray() );
    }
    //如果不是该程序的数据,也停止读取
    quint32 head;
    in >> head;
    if(head != msgHead){
        return Msg( MsgType::UNDEFINED, QByteArray() );
    }
    //继续读取
    quint16 tmp_type;
    QByteArray content;
    in >> tmp_type;
    in >> content;
    return Msg( (MsgType)(tmp_type), content );
}

