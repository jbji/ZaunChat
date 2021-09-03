#ifndef MSG_H
#define MSG_H

#include <QObject>
#include "msgtype.h"

/*
 *
    MSG的标准QByteArray编码格式:
    |4:dataSize|4:head|2:type|?:content|
    具体说明:
    dataSize: 占 4 个字节, quint32, 用于验证是否完整接收到了数据包
    head    : 占 4 个字节, quint32, 用于验证是不是该程序的数据包
    type    : 占 2 个字节, quint16, 用于标识数据包类型
    content : 占未定字节 , 数据包的具体内容, 取决于type, 由handler解析

    创建QByteArray时使用QDataStream以流的方式写入
    获得QByteArray时也适用流的方式读取.
    QDataStream需要setVersion

    解析Msg时以Map注册Handler类的方式, 将具体解析方法打包在Handler类中.
    例如, QMap<MsgType, MsgHandler>

*/



//普通的文本消息

//以下是涉及到具体的Content编码
//图片的名称 图片的大小 图片的二进制流

//文件的文件名 文件的大小 文件的二进制流 服务器接收到文件要rename

class Msg
{
public:
    //用内容构造一个Msg包
    Msg(MsgType type, const QByteArray & content);

    //将接收到QByteArray的转换成Msg对象
    //如果返回type是UNDEFINED, 说明转换失败
    static Msg fromQByteArray(const QByteArray & type_and_content); //不包含开头8个字节
    static Msg fromFullQByteArray(const QByteArray & full_received); //包含开头8个字节
    //example: MsgHandler()->parse( Msg::fromQByteArray(type_and_content) );

    //转换成可以直接发送的QByteArray数组
    QByteArray toQByteArray();
    //example: clientConnection->write( Msg(type, content).toQByteArray() );

    //给Handler提供直接操作Msg的接口
    MsgType getType();
    QByteArray & getContent();

    static quint32 msgHead;

private:
    // |4:dataSize|4:head|2:type|?:content|
    quint32 dataSize;

    MsgType type;
    QByteArray content;
};

#endif // MSG_H
