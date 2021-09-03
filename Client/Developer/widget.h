#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "new_windows.h"
#include "DataModel/datamodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_login_button_clicked();

    void on_register_button_clicked();

    //日志小窗口的槽函数
    void showLog(QString);

    void autoScroll();

private slots:
    //显示注册登录状态的槽函数
    void showRegisterSuccessful(UserInfo info);
    void showRegisterFailed();
    void showRegisterGroupSuccessful(GroupInfo info);
    void showRegisterGroupFailed();

    void showLoginSuccessful(UserInfo info);
    void showLoginFailed();

    void on_pushButton_clicked();

    //显示消息的槽函数
    void showChatMessage(ChatMessage msg);
    void requestChatFile(ChatMessage msg);
    void showReceivedFile(FileMeta info);
    void showReceivedImg(QString path, FileMeta info);

    void on_pushButton_2_clicked();

    //显示添加好友信息的槽函数
    void showAddFriendSuccessful();
    void showAddFriendFailed(MsgType type);
    void showFriendRequest(UserInfo cmsg);
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    //debug专用
    void showUserInfo(UserInfo info);
    //end

    //群聊
    void showModifyUsernameSuccess(QString newUsername);
    void showAddGroupSuccess(GroupInfo info);
    void showAddGroupFailed(MsgType type);
    void showGroupChatMessage(GroupChatMessage msg);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::Widget *ui;
    new_windows *new_win;
};
#endif // WIDGET_H
