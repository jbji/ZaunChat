#ifndef CHAT_MSG_HANDLER_H
#define CHAT_MSG_HANDLER_H

#include <QObject>

#include "DataModel/datamodel.h"
#include "msghandler.h"

class ChatMsgHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit ChatMsgHandler(QObject *parent = nullptr);
    //这个函数拿到服务端传来的Msg消息, 然后将其转换成ChatMessage对象
    //并进行emit
    void parse(Msg & msg);

signals:
    //parse处理完以后, 发射信号readyShowChatMsg
    //GUI部分拿到chat_msg, 并将其显示出来
    void readyShowChatMsg(ChatMessage chat_msg);
    void readyShowWindowShake(ChatMessage package);//接收到窗口抖动 package里会存储是谁发过来的窗口抖动.
    void readyShowChatPic(ChatMessage chat_msg);//接收到图片
    void readyShowChatEmo(ChatMessage chat_msg);//接收到表情
    void readyShowChatFile(ChatMessage chat_msg);//接收到文件
};

#endif // CHAT_MSG_HANDLER_H
