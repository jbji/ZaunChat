#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QObject>
//聊天信息类, 一条信息就是一个该类的instance
//暂时没有考虑图片的存储问题
class ChatMessage
{

public:
    explicit ChatMessage(quint32 sender, quint32 receiver, const QString & content);
    //getters
    quint32 getSender() const;
    quint32 getReceiver() const;
    QString & getContent();
    QString getTimeStamp(); //获得消息的时间戳
signals:

private:
    //要不要存储时间戳呢?
    friend class DataDB;
    quint32 _sender;
    quint32 _receiver;
    QString _time_stamp; //时间戳在构造函数中创建
    QString _content;

public:
    //暂时只有ClientController和Chat的Handler需要访问的函数 不确定是否需要子类
    //转换函数, 便于丢给Msg后再发送
    //对于ChatMessage的QByteArray编码方式
    // | quint32 sender | quint32 receiver |  quint32 time_stamp size | time_stamp | quint32 content size | content |

    static ChatMessage fromQByteArray(QByteArray chat_msg);
    QByteArray toQByteArray();

};

#endif // CHATMESSAGE_H
