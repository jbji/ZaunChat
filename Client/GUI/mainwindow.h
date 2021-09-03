#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSplitter>
#include <QTableWidget>
#include <QListWidget>
#include <QString>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QPainter>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include "user.h"

#include "DataModel/datamodel.h"
#include "GUI/addfriendalert.h"
#include "DataModel/datamodel.h"
#include "GUI/addfriend.h"
#include "Developer/widget.h"
#include "GUI/chooseimage.h"
#include "GUI/choosefile.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUserInfo(); //显示头像和昵称和id
    void getFriendInfo(); //获取好友信息
    void initUserInfo(UserInfo info);
    static addfriendalert * GetAddfriendalert();
    static addfriend * GetAddfriend();
    static chooseFile* GetChooseFlie();
    static ChooseImage* GetChooseImage();
   // void onShakeWindow(ChatMessage msg);

private slots:
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();
    void getLastchatInfo(); //获取最近联系人信息
    void GroupList(); //获取好友申请信息
    //void getRecords(QString name); //获取历史记录
    void sendtxt(); //发送聊天信息

    void sendtxttoGroup(); //发送群聊信息
    void sendshake();//抖动窗口
    void openAlterimgWidget(); //打开修改头像的窗口
    void openAlternameWidget(); //打开修改用户名的窗口
    void openAlterpwdWidget(); //打开修改密码的窗口

    void openAddFriendsWidget();
    void openAddGroupWidget();
    void openCreateGroupWidget();

    void openAddFriendAlertWidget(UserInfo sender);

    void openChatWindow();
    void openGroupChatWindow();
    void closeChatWindow();

    void on_friendlist_clicked();
    void on_chatlist_clicked();
    void on_friendrequest_clicked();
    void showChatMessage(ChatMessage msg);
    void showGroupChatMessage(GroupChatMessage groupchatmsg);
    void onShakeWindow(ChatMessage msg);//窗口抖动
    void sendfile();//发送文件
    void sendimg();
    void shotScreen();
    void changeColor();
    void showModifyUsernameSuccess(QString username);
    void RefreshFriendList();
    void RefreshGroupList();
    void opendeveloperModeWidget();

    void showReceivedImg(QString Path, FileMeta info);
    void showImgMessage(QString img, quint32 receiver);
    void showFileMessage(ChatMessage chat_msg);
    void showMyImgMessage(QString img, quint32 receiver);

    friend class ChooseImage;

protected:
        //void paintEvent(QPaintEvent *event); //绘制聊天气泡
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件
signals:
    void ALLFINISH();
private:
    Ui::MainWindow *ui;
    QString imgPath; //用户头像
    QString name; //用户名
    quint32 id; //用户账号
    QString pwd; // 用户密码
    QTextEdit *txt;  //文本编辑框
    QToolButton* Send;//发送按钮
    QToolButton* SendtoGroup;
    QToolButton* Shake;//抖动按钮
    QToolButton* sendFile; //文件发送按钮
    QToolButton* sendImg;//图片发送按钮
    QToolButton* screenShot;//截图按钮
    QFrame* dialogSetting; //操作栏，包括发文件、气泡颜色更改等按钮
    QToolButton* changeTheme; //更改界面主题颜色
    QListWidget *pchatw; //当前聊天窗口
    User* friendInfo; //当前聊天对象
    QToolButton* Friend; //当前聊天对象的头像
    QLabel* friendName;//当前聊天对象的用户名
    //QMap<QToolButton*,QListWidget*> chatMap;
    //记录好友信息与对应btn及聊天窗口的关系
   QMap<quint32,QListWidget*> chatMap;
   QMap<QToolButton*,User*> friendMap;
   QMap<quint32,QToolButton*> Mapfriend;

   //记录群聊信息与对应btn及聊天窗口的关系
   QMap<quint32,QListWidget*> groupchatMap;
   QMap<QToolButton*,User*> groupMap;
   QMap<quint32,QToolButton*> Mapgroup;
    QAction* changeImg;
    QAction* changeName;
    QAction* changePwd;
    QMenu* settings;
    QAction* addFriendAction;
    QAction* addGroupAction;
    QAction* createGroupAction;
    QAction* developerMode;
    QMenu* addMenu;
    QMenu* ColorMenu;
    QString color; //气泡颜色
    QVBoxLayout *layer1;
    QVBoxLayout *layer2;
    QVBoxLayout *layer3;
    QFrame *currentframe;

    QPoint m_point;

    static addfriendalert * newWindow;
    static addfriend * newAddfriend;
    static ChooseImage * cImag;
    static chooseFile * cFile;

    User * getFriend(){
        return friendInfo;
    }
};

#endif // MAINWINDOW_H
