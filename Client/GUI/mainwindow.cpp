#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "itemwidget.h"
#include "user.h"
#include "alterimg.h"
#include "altername.h"
#include "alterpwd.h"
#include "addfriend.h"
#include "addgroup.h"
#include "creategroup.h"
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"

#include "DataModel/chatmessage.h"

#include "addfriendalert.h"
#include "QAbstractAnimation"
#include "QPropertyAnimation"
#include "choosefile.h"
#include "Network/ResAssist/localcache.h"
addfriendalert * MainWindow:: newWindow = nullptr;
addfriend * MainWindow:: newAddfriend = nullptr;
chooseFile * MainWindow:: cFile = nullptr;
ChooseImage * MainWindow:: cImag = nullptr;
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(ALLFINISH()),ClientController::GetClientInstance(),SLOT(requestOfflineMsg()));
    // 第一个参数是设置无边框。第二个参数是允许任务栏按钮右键菜单，第三个参数是允许最小化与还原
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(20); //模糊度
    ui->widget->setGraphicsEffect(shadow);


    //初始化，这里用户信息应该用userinfo类
    imgPath = ":/img/defaultimg.png";

    //初始化
    pchatw = NULL;
    ClientController * client = ClientController::GetClientInstance();
    friendInfo = new User;
    friendInfo->Set(client->getMyInfo().getID(),client->getMyInfo().getName(),client->getMyInfo().getAvatarName());
    layer1 = new QVBoxLayout(ui->frame1);
    layer2 = NULL;
    layer3 = new QVBoxLayout(ui->frame3);
    ui->frame1->hide();
    ui->frame2->hide();
    ui->frame3->hide();
    currentframe = ui->frame1;
    currentframe->show();
    ui->friendlist->setStyleSheet("QToolButton{background-color: rgb(255, 240, 211);\
                                    border:none;border-top:1px solid rgb(219,132,52);border-left:1px solid rgb(219,132,52);\
                                    border-right:1px solid rgb(219,132,52);border-top-left-radius:10px;border-top-right-radius:10px;}");
    Friend = new QToolButton(ui->dialog);
    Friend->setIconSize(QSize(40,40));
    Friend->hide();
    friendName = new QLabel(ui->dialog);
    friendName->hide();
    ui->closeButton2->hide();

    //聊天的发送框
    txt= new QTextEdit(ui->dialog);
    txt->setGeometry(1, 430, 550, 130);
    txt->setStyleSheet("QTextEdit{background-color:rgb(255,255,255);border:none;border-top:1px solid rgb(219,132,52)}");
    txt->hide();

    //聊天发送按钮
    Send = new QToolButton(ui->dialog);
    Send->setText("Send");
    Send->setGeometry(480,510,60,30);
    Send->setStyleSheet("QToolButton{background-color:rgb(254,208,142);color:rgb(160,80,11);\
                        border:1px solid rgb(219,132,52);border-radius:5px;}");
    connect(Send,SIGNAL(clicked()),this,SLOT(sendtxt()));
    Send->hide();

    //群聊发送按钮
        SendtoGroup = new QToolButton(ui->dialog);
        SendtoGroup->setText("Send2");
        SendtoGroup->setGeometry(480,510,60,30);
        SendtoGroup->setStyleSheet("QToolButton{background-color:rgb(254,208,142);color:rgb(160,80,11);\
                            border:1px solid rgb(219,132,52);border-radius:5px;}");
        connect(SendtoGroup,SIGNAL(clicked()),this,SLOT(sendtxttoGroup()));
        SendtoGroup->hide();

    //窗口抖动按钮
    Shake=new QToolButton(ui->dialog);
    Shake->setText("Shake");
    Shake->setGeometry(400,510,60,30);
    Shake->setStyleSheet("QToolButton{background-color:rgb(254,208,142);color:rgb(160,80,11);\
                        border:1px solid rgb(219,132,52);border-radius:5px;}");
    connect(Shake,SIGNAL(clicked()),this,SLOT(sendshake()));
    Shake->hide();

    dialogSetting = new QFrame(ui->dialog);
    dialogSetting->setStyleSheet("background-color:rgb(255,255,255);border:none;");
    dialogSetting->setGeometry(1,400,550,30);
    dialogSetting->hide();
    //文件发送按钮
    sendFile = new QToolButton(dialogSetting);
    sendFile->setIcon(QIcon(":/img/sendFilebtn.png"));
    sendFile->setIconSize(QSize(28,28));
    sendFile->setGeometry(10,0,28,28);
    sendFile->setStyleSheet("QToolButton{border:none;}\
                        QToolButton::hover{border:none;background-color:rgb(220,220,220);}");
    connect(sendFile,SIGNAL(clicked()),this,SLOT(sendfile()));
    sendFile->hide();

    //图片发送按钮
    sendImg = new QToolButton(dialogSetting);
    sendImg -> setIcon(QIcon(":/img/sendImgbtn.png"));
    sendImg -> setIconSize(QSize(28, 28));
    sendImg -> setGeometry(90,0,28,28);
    sendImg -> setStyleSheet("QToolButton{border:none;}\
                        QToolButton::hover{border:none;backgroud-color:rgb(220,220,220);}");
    connect(sendImg,SIGNAL(clicked()),this,SLOT(sendimg()));
    sendImg -> hide();

    //截图按钮
    screenShot = new QToolButton(dialogSetting);
    screenShot -> setIcon(QIcon(":/img/scShotbtn.png"));
    screenShot -> setIconSize(QSize(28, 28));
    screenShot -> setGeometry(130,0,28,28);
    screenShot -> setStyleSheet("QToolButton{border:none;}\
                        QToolButton::hover{border:none;backgroud-color:rgb(220,220,220);}");
    connect(screenShot,SIGNAL(clicked()),this,SLOT(shotScreen()));
    screenShot -> hide();

    //气泡颜色更改按钮
    changeTheme = new QToolButton(dialogSetting);
    changeTheme->setIcon(QIcon(":/img/colorChangebtn.png"));
    changeTheme->setIconSize(QSize(28,28));
    changeTheme->setGeometry(50,0,28,28);
    changeTheme->setStyleSheet("QToolButton{border:none;}\
                        QToolButton::hover{border:none;background-color:rgb(220,220,220);}");
    color = "rgb(254,208,142)";
    ColorMenu = new QMenu(ui->dialog);
    QString Colors[5] = {"默认", "红色", "蓝色", "绿色", "紫色"};
    for(int i=0;i<5;i++)
    {
        QAction* colorAction = new QAction(Colors[i]);
        colorAction->setObjectName(QString::number(i));
        connect(colorAction,SIGNAL(triggered()),this,SLOT(changeColor()));
        ColorMenu->addAction(colorAction);
    }
    changeTheme->setPopupMode(QToolButton::InstantPopup);
    changeTheme->setMenu(ColorMenu);
    changeTheme->setStyleSheet("QToolButton::menu-indicator{image:none}");
    changeTheme->hide();
    //加载用户和好友信息
    getFriendInfo();
    qDebug()<<"start getlast";
    getLastchatInfo();
    qDebug()<<"grouplist";
    GroupList();

    //右上角的设置，包括几个修改动作
    settings = new QMenu(ui->dialog);
    changeImg = new QAction(tr("修改头像"));
    connect(changeImg,SIGNAL(triggered()),this,SLOT(openAlterimgWidget()));
    settings->addAction(changeImg);
    changeName = new QAction(tr("修改昵称"));
    connect(changeName,SIGNAL(triggered()),this,SLOT(openAlternameWidget()));
    settings->addAction(changeName);
    changePwd = new QAction("修改密码");
    connect(changePwd,SIGNAL(triggered()),this,SLOT(openAlterpwdWidget()));
    settings->addAction(changePwd);
    developerMode = new QAction("开发者模式");
    connect(developerMode,SIGNAL(triggered()),this,SLOT(opendeveloperModeWidget()));
    settings->addAction(developerMode);
    ui->settingButton->setPopupMode(QToolButton::InstantPopup);
    ui->settingButton->setMenu(settings);
    ui->settingButton->setStyleSheet("QToolButton::menu-indicator{image:none}");

    connect( (ChatMsgHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::MSG_PLAIN_TEXT),
             &ChatMsgHandler::readyShowChatMsg,
             this,
             &MainWindow::showChatMessage
             );
    connect( (GroupMsgHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::GROUP_MSG_PLAIN_TEXT),
                 &GroupMsgHandler::groupMsgReceiveSuccess,
                 this,
                 &MainWindow::showGroupChatMessage
                 );
    connect( (FriendRequestHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::REQUEST_ADD_FRIEND),
             &FriendRequestHandler::readyShowFriendRequest,
             this,
             &MainWindow::openAddFriendAlertWidget);

    connect((ChatMsgHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::MSG_WINDOW_SHAKE),
            &ChatMsgHandler::readyShowWindowShake,
            this,
            &MainWindow::onShakeWindow
            );
    connect((ModifyUserNameResultHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::MODIFY_USERNAME_SUCCESS),
            &ModifyUserNameResultHandler::modifyUserNameSuccess,
            this,
            &MainWindow::showModifyUsernameSuccess);
    connect(GetAddfriendalert(),SIGNAL(refreshFriendList()),this,SLOT(RefreshFriendList()));
    connect(GetAddfriend()->GetAddSuccess(),SIGNAL(refreshFriendList()),this,SLOT(RefreshFriendList()));
    connect((RegisterGroupHandler*) HandlerReg::GetRegObj()->getHandler(MsgType::REGISTER_GROUP_SUCCESS),
            &RegisterGroupHandler::refreshGroupList,
            this,
            &MainWindow::RefreshGroupList);
    connect((AddGroupResultHandler*) HandlerReg::GetRegObj()->getHandler(MsgType::ADD_GROUP_SUCCESS),
            &AddGroupResultHandler::refreshGroupList,
            this,
            &MainWindow::RefreshGroupList);
    connect(LocalCache().GetInstance(), &LocalCache::alreadyReceivedImg,
            this, &MainWindow::showReceivedImg);
    connect((ChatMsgHandler*)HandlerReg::GetRegObj()->getHandler(MsgType::MSG_FILE),
        &ChatMsgHandler::readyShowChatFile,
        this,
        &MainWindow::showFileMessage);
    connect(GetChooseImage(),SIGNAL(readyShowMyIMG(QString,quint32)),this,SLOT(showMyImgMessage(QString, quint32)));

    connect(ClientController::GetClientInstance(),SIGNAL(readyShowMyPIC(QString,quint32)),this,SLOT(showMyImgMessage(QString,quint32)));
    //添加好友群聊的菜单栏
    addMenu = new QMenu(ui->list);
    addFriendAction = new QAction(tr("添加好友"));
    connect(addFriendAction,SIGNAL(triggered()),this,SLOT(openAddFriendsWidget()));
    addMenu->addAction(addFriendAction);
    addGroupAction = new QAction(tr("添加群聊"));
    connect(addGroupAction,SIGNAL(triggered()),this,SLOT(openAddGroupWidget()));
    addMenu->addAction(addGroupAction);
    createGroupAction = new QAction("创建群聊");
    connect(createGroupAction,SIGNAL(triggered()),this,SLOT(openCreateGroupWidget()));
    addMenu->addAction(createGroupAction);
    ui->friendadding->setPopupMode(QToolButton::InstantPopup);
    ui->friendadding->setMenu(addMenu);
    ui->friendadding->setStyleSheet("QToolButton::menu-indicator{image:none}");
}

void MainWindow::showModifyUsernameSuccess(QString username){
    name=username;
    setUserInfo();
    QToolButton * tmp = Mapfriend[ClientController::GetClientInstance()->getMyInfo().getID()];
    tmp->setText(" "+username);
}

void MainWindow::initUserInfo(UserInfo info)
{
    this->id = info.getID();
    this->name = info.getName();
    this->pwd = info.getPwd();
}

void MainWindow::sendshake(){
    ClientController::GetClientInstance()->sendWindowShake(friendInfo->getid());
}

void MainWindow::openCreateGroupWidget(){
        createGroup*w=new createGroup;
        w->show();
    }
void MainWindow::showChatMessage(ChatMessage msg){
    qDebug()<<"showChatMessage:"<<msg.getContent();
    quint32 nowchat=msg.getSender();
    quint32 nowuserinfo=friendInfo->getid();
    if(nowchat==nowuserinfo){
        ItemWidget* item=new ItemWidget(this);
        item->setColor(color);
        int height=item->SetFriendsData(nowchat,":/img/defaultimg.png",msg.getContent());
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        pchatw->addItem(line);
        pchatw->setItemWidget(line, item);
        pchatw->scrollToBottom();
    }else{
        QListWidget* nowwidget=chatMap[nowchat];
        ItemWidget* item=new ItemWidget(nowwidget);
        item->setColor(color);
        int height=item->SetFriendsData(nowchat,":/img/defaultimg.png",msg.getContent());
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        nowwidget->addItem(line);
        nowwidget->setItemWidget(line, item);
        QToolButton* nowbutton=Mapfriend[nowchat];
        nowbutton->setStyleSheet("background-color:rgb(255,0,0);front-size:20px;");
    };
}
void MainWindow::showGroupChatMessage(GroupChatMessage groupchatmsg){
    ChatMessage msg = groupchatmsg.getChatMessage();
    UserInfo sender = groupchatmsg.getUserInfo();
    quint32 nowchat = msg.getReceiver();      // 当前群聊id
    quint32 nowuserinfo=friendInfo->getid();   // 当前群聊界面的群聊id
    if(nowchat==nowuserinfo){
        ItemWidget* item=new ItemWidget(this);
        item->setColor(color);
        int height=item->SetFriendsData(msg.getSender(),":/img/defaultimg.png",msg.getContent());
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        pchatw->addItem(line);
        pchatw->setItemWidget(line, item);
        pchatw->scrollToBottom();
    }else{
        QListWidget* nowwidget=groupchatMap[nowchat];
        ItemWidget* item=new ItemWidget(nowwidget);
        item -> setColor(color);
        int height=item->SetFriendsData(msg.getSender(),":/img/defaultimg.png",msg.getContent());
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        nowwidget->addItem(line);
        nowwidget->setItemWidget(line, item);
        QToolButton* nowbutton=Mapgroup[nowchat];
        nowbutton->setStyleSheet("background-color:rgb(255,0,0);front-size:20px;");
    };
}
void MainWindow::openAddFriendAlertWidget(UserInfo sender)
{
    addfriendalert* newWindow = MainWindow::GetAddfriendalert();
    newWindow->setSender(sender);
    newWindow->setReceiverId(ClientController::GetClientInstance()->getMyInfo().getID());
    newWindow->setAlertText();
    newWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//关闭窗口
void MainWindow::on_closeButton_clicked()
{
    ClientController::GetClientInstance()->requestLogout(this->id);
    this->close();
}

//窗口最小化
void MainWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
}


void MainWindow::getFriendInfo()
{
    //Log::GetLogObj()->writeLog("["+QString::number(ClientController::GetClientInstance()->getMyInfo().getID())+"]'s Friends are:");
    qDebug()<<"success getfriend start";

    auto i = ClientController::GetClientInstance()->getFriendList();
      //int n=i->size();
      QList<QString> list;
      QList<QString> Icon;
      QList<QString> name;
      for(auto &j : *i){
          list.append( QString::number(j.getID()));
          Icon.append(":/img/defaultimg.png");
          name.append(j.getName());

      }
      //Log::GetLogObj()->writeLog(list);
    int n = list.size();
    qDebug()<<"friendlist:"<<n;
    //QString Icon[10] = {":/img/defaultimg.png", ":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png"};
    //QString name[10] = {"BMY", "ME","a","a","a","a","a","a","a","a"};
    //quint32 id[10] = {100009, 100010, 2, 3, 4, 5, 6, 7, 8, 9};

    delete layer1;
    layer1 = new QVBoxLayout(ui->frame1);
    for(int i = 0; i < n; i++)
    {
        if(chatMap.contains(list[i].toInt())){
            QToolButton* toolbtn = Mapfriend[list[i].toInt()];
            layer1->addWidget(toolbtn);
            continue;
        }
        User* u = new User(list[i].toInt(), name[i], Icon[i]);
        QToolButton* toolbtn = new QToolButton;
        toolbtn->setIconSize(QSize(40,40));
        toolbtn->setObjectName(list[i]);  //按键名为id
        toolbtn->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;font-size:20px;}");
        toolbtn->setIcon(QIcon(u->getImage()));
        toolbtn->setText(" "+u->getUsername());
        toolbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //聊天对话框
        QListWidget* listw = new QListWidget(ui->dialog);
        listw->setGeometry(1, 43, 549, 357);
        listw->setStyleSheet("QListWidget{background-color:rgb(255,255,255);border:none;\
                                border-bottom:1px solid rgb(213,132,52);\
                                border-top:1px solid rgb(213,132,52);}");
        listw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listw->hide();
        //friendMap.insert(toolbtn,u);
        friendMap[toolbtn]=u;
        Mapfriend[u->getid()]=toolbtn;
        chatMap[u->getid()]=listw;
        //Mapfriend.insert(u->getid(),toolbtn);
        //chatMap.insert(u->getid(),listw);

        connect(toolbtn,SIGNAL(clicked()),this,SLOT(openChatWindow())); //实现通信

        layer1->addWidget(toolbtn);
       // layer1->addStretch();
    }
    layer1->addStretch();
    emit ALLFINISH();
}


//最近聊天列表信息
void MainWindow::getLastchatInfo()
{
    //int n =getfriendsNum(); 获取好友数量
    //QString* Icon1 = getfriendsIcon(); 获取好友头像
    //Qstring* name1 = getfriendsName(); 获取好友昵称
    int n = 5;
    QString Icon[10] = {":/img/defaultimg.png", ":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png",":img/defaultimg.png",":/img/defaultimg.png",":/img/defaultimg.png"};    QString name[10] = {"Alice", "Bob","a","a","a","a","a","a","a","a"};
    quint32 id[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    layer2 = new QVBoxLayout(ui->frame2);

    for(int i = 0; i < n; i++)
    {

        User* u = new User(id[i], name[i], Icon[i]);
        QToolButton* toolbtn = new QToolButton;
        toolbtn->setIconSize(QSize(40,40));
        toolbtn->setObjectName(QString(u->getid()));  //按键名为id
        toolbtn->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;font-size:20px;}");
        toolbtn->setIcon(QIcon(u->getImage()));
        toolbtn->setText(" "+u->getUsername());
        toolbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        friendMap.insert(toolbtn,u);

        connect(toolbtn,SIGNAL(clicked()),this,SLOT(openChatWindow())); //实现通信

        layer2->addWidget(toolbtn);
    }

    layer2->addStretch();
}

void MainWindow::GroupList()
{
    //Log::GetLogObj()->writeLog("["+QString::number(ClientController::GetClientInstance()->getMyInfo().getID())+"]'s Friends are:");
    qDebug()<<"success getfriend start";

    //这里应该是获取群聊信息

    auto i = ClientController::GetClientInstance()->getGroupList();
      //int n=i->size();
      QList<QString> list;
      QList<QString> Icon;
      QList<QString> name;
      for(auto &j : *i){
          list.append( QString::number(j.getID()));
          Icon.append(":/img/defaultimg.png");
          name.append(j.getName());

      }
      //Log::GetLogObj()->writeLog(list);
    int n = list.size();
    qDebug()<<"GroupList:"<<n;
    delete  layer3;
    layer3 = new QVBoxLayout(ui->frame3);

    for(int i = 0; i < n; i++)
    {
        if(groupchatMap.contains(list[i].toInt())){
            QToolButton* toolbtn = Mapgroup[list[i].toInt()];
            layer3->addWidget(toolbtn);
            continue;
        }
        User* u = new User(list[i].toInt(), name[i], Icon[i]);
        QToolButton* toolbtn = new QToolButton;
        toolbtn->setIconSize(QSize(40,40));
        toolbtn->setObjectName(list[i]);  //按键名为id
        toolbtn->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;font-size:20px;}");
        toolbtn->setIcon(QIcon(u->getImage()));
        toolbtn->setText(" "+u->getUsername());
        toolbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //聊天对话框
        QListWidget* listw = new QListWidget(ui->dialog);
        listw->setGeometry(1, 43, 549, 357);
        listw->setStyleSheet("QListWidget{background-color:rgb(255,255,255);border:none;\
                                border-bottom:1px solid rgb(219,132,52);\
                                border-top:1px solid rgb(219,132,52);}");
        listw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listw->hide();
        groupMap[toolbtn]=u;
        Mapgroup[u->getid()]=toolbtn;
        groupchatMap[u->getid()]=listw;

        connect(toolbtn,SIGNAL(clicked()),this,SLOT(openGroupChatWindow())); //实现通信

        layer3->addWidget(toolbtn);
    }
    layer3->addStretch();

}

void MainWindow::setUserInfo()
{
    /*QToolButton *imglb = new QToolButton(ui->list);
    QImage img;

    img.load(imgPath); //加载图片
    img = img.scaled(50,50,Qt::IgnoreAspectRatio); //调节图片大小
    imglb->setPixmap(QPixmap::fromImage(img));
    //设置lable相对于父类的位置
    imglb->setGeometry(img.rect());
    imglb->show();*/

    //头像
    ui->imgbtn->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;width:40px;height:40px;}");
    ui->imgbtn->setIcon(QIcon(imgPath));

    //用户名
    ui->username->setText(name);

    //用户id
    QString str = "id:";
    //qDebug()<<QString(id);
    str = str.append(QString::number(id));
    ui->userid->setText(str);

}

void MainWindow::openChatWindow()
{
    QToolButton* Sender = qobject_cast<QToolButton*>(sender());
    if(friendInfo!=NULL)
    {
        qDebug()<<"YES";
        if(friendInfo->getid()<1000000){
            Mapfriend[friendInfo->getid()]->setStyleSheet("color:rgb(0,0,0);font-size:20px;");
        }
        else{
            Mapgroup[friendInfo->getid()]->setStyleSheet("color:rgb(0,0,0);font-size:20px;");
        }
    }
    //QString name = Sender->text();
    //int id = Sender->objectName().toInt();
    //qDebug() << name;

    //记录当前聊天对象信息
    if(!friendMap.contains(Sender)){
        qDebug()<<"HERE"; return;
    }
    friendInfo = friendMap[Sender];
    qDebug()<<friendInfo->getid();
    Sender->setStyleSheet("color:rgb(180,100,22);font-size:20px;");

    //在聊天框显示头像
    Friend->setIcon(Sender->icon());
    Friend->setIconSize(QSize(39,39));
    Friend->setGeometry(10,1,39,39);
    Friend->setStyleSheet("QToolButton{border:none;}");
    Friend->show();
    //在聊天框显示用户名
    friendName->setText(Sender->text());
    friendName->setGeometry(60,10,100,30);
    friendName->setStyleSheet("QLabel{border:none;}");
    friendName->setAlignment(Qt::AlignVCenter);
    friendName->show();

    //在聊天窗口显示关闭按钮
    ui->closeButton2->show();
    connect(ui->closeButton2,SIGNAL(clicked()),this,SLOT(closeChatWindow()));

    //显示相应对话框
    if(pchatw != NULL)
        pchatw->hide();
    pchatw = chatMap[friendInfo->getid()];
    qDebug() << pchatw->objectName();
    pchatw->show();

    ui->closeButton2->show();


    //聊天框的编辑框 缺滚动条
    txt->show();

    //发送按钮
    Send->show();
    SendtoGroup->hide();
    Shake->show();

    //各种设置按钮
    dialogSetting->show();
    sendFile->show();
    changeTheme->show();
    sendImg -> show();
    screenShot->show();
}
void MainWindow::openGroupChatWindow()
{
    QToolButton* Sender = qobject_cast<QToolButton*>(sender());
    if(friendInfo!=NULL)
    {
        qDebug()<<Mapgroup[friendInfo->getid()]<<"asddddd";
        if(friendInfo->getid()<1000000){
            Mapfriend[friendInfo->getid()]->setStyleSheet("color:rgb(0,0,0);font-size:20px;");
        }
        else{
            Mapgroup[friendInfo->getid()]->setStyleSheet("color:rgb(0,0,0);font-size:20px;");
        }
    }
    //QString name = Sender->text();
    //int id = Sender->objectName().toInt();
    //qDebug() << name;

    //记录当前聊天对象信息
    friendInfo = groupMap[Sender];
    Sender->setStyleSheet("color:rgb(180,100,22);font-size:20px;");

    //在聊天框显示头像
    Friend->setIcon(Sender->icon());
    Friend->setIconSize(QSize(39,39));
    Friend->setGeometry(10,1,39,39);
    Friend->setStyleSheet("QToolButton{border:none;}");
    Friend->show();

    //在聊天框显示用户名
    friendName->setText(Sender->text());
    friendName->setGeometry(60,10,100,30);
    friendName->setStyleSheet("QLabel{border:none;}");
    friendName->setAlignment(Qt::AlignVCenter);
    friendName->show();

    //在聊天窗口显示关闭按钮
    ui->closeButton2->show();
    connect(ui->closeButton2,SIGNAL(clicked()),this,SLOT(closeChatWindow()));


    //显示相应对话框
    if(pchatw != NULL)
        pchatw->hide();
    pchatw = groupchatMap[friendInfo->getid()];
    qDebug() << pchatw->objectName();
    pchatw->show();

    ui->closeButton2->show();


    //聊天框的编辑框 缺滚动条
    txt->show();

    //发送按钮
    Send->hide();
    SendtoGroup->show();
    Shake->show();

    //各种设置按钮
    dialogSetting->show();
    sendFile->show();
    changeTheme->show();
    sendImg -> show();
    screenShot->show();
}

void MainWindow::sendtxt()
{

    //在界面显示txt
    if(txt->toPlainText()=="") return;
    ItemWidget* itemw = new ItemWidget(this);
    itemw->setColor(color);
    int height=itemw->SetMyData(id,":/img/defaultimg.png",txt->toPlainText());
    QListWidgetItem* line = new QListWidgetItem();
    line->setSizeHint(QSize(350, height));
    pchatw->addItem(line);
    pchatw->setItemWidget(line, itemw);
    pchatw->scrollToBottom();
    //发送信息
    qDebug()<<friendInfo->getid();
    qDebug()<<txt->toPlainText();
    ClientController::GetClientInstance()->sendChatMessage(friendInfo->getid(),
                                      txt->toPlainText());
    //sendChatMessage(ChatMessage & chat_msg);

    // 消息编辑栏清空
    txt->clear();

}
void MainWindow::sendtxttoGroup()
{
    //在界面显示txt
    if(txt->toPlainText()=="") return;
    ItemWidget* itemw = new ItemWidget(this);
    itemw -> setColor(color);
    //这里应该有设置气泡颜色的函数，但是这个版本好像没有

    int height=itemw->SetMyData(id,":/img/defaultimg.png",txt->toPlainText());
    QListWidgetItem* line = new QListWidgetItem();
    line->setSizeHint(QSize(350, height));
    pchatw->addItem(line);
    pchatw->setItemWidget(line, itemw);
    pchatw->scrollToBottom();
    //发送信息
    qDebug()<<friendInfo->getid();
    qDebug()<<txt->toPlainText();
    ClientController::GetClientInstance()->sendGroupChatMessage(friendInfo->getid(),
                                      txt->toPlainText());
    //sendChatMessage(ChatMessage & chat_msg);

    // 消息编辑栏清空
    txt->clear();

}
void MainWindow::sendfile()
{
    chooseFile* w = GetChooseFlie();
    w -> setFriendInfo(friendInfo);
    w->show();
}
void MainWindow::sendimg(){
    ChooseImage * w = GetChooseImage();
    w -> setFriendInfo(friendInfo);
    w -> show();
}

void MainWindow::shotScreen()
{
    //截图操作
    ClientController * client = ClientController::GetClientInstance();
    client -> requestFullScreenShot(friendInfo->getid());
}

void MainWindow::closeChatWindow()
{
    pchatw->hide();
    //pchatw = NULL;
    Friend->hide();
    friendName->hide();
    ui->closeButton2->hide();
    txt->hide();
    Send->hide();
    SendtoGroup->hide();
    Shake->hide();
    //各种设置按钮
    dialogSetting->hide();
    sendFile->hide();
    sendImg->hide();
    screenShot->hide();
    changeTheme->hide();
}

void MainWindow::openAlterimgWidget()
{
    alterImg* w = new alterImg;
    w->show();
}

void MainWindow::openAlternameWidget()
{
    alterName* w = new alterName;
    w->show();
}

void MainWindow::openAlterpwdWidget()
{
    alterPwd* w = new alterPwd;
    w->show();
}

void MainWindow::openAddFriendsWidget()
{
    addfriend* w =GetAddfriend();
    w->show();
}

void MainWindow::openAddGroupWidget()
{
    addgroup* w = new addgroup;
    w->show();
}

void MainWindow::changeColor()
{
    QAction* Sender = qobject_cast<QAction*>(sender());
    QString colorRGB[5] = {"rgb(254,208,142)", "rgb(254, 147, 152)", "rgb(153,224,254)", "rgb(137,214,146)", "rgb(221,188,254)"};
    int i =Sender->objectName().toUInt();
    color = colorRGB[i];
}

void MainWindow::on_friendlist_clicked()
{
    currentframe->hide();
    currentframe = ui->frame1;
    ui->friendlist->setStyleSheet("QToolButton{background-color: rgb(255, 240, 211);\
                                    border:none;border-top:1px solid rgb(219,132,52);border-left:1px solid rgb(219,132,52);\
                                    border-right:1px solid rgb(219,132,52);border-top-left-radius:10px;border-top-right-radius:10px;}");
    ui->chatlist->setStyleSheet("QToolButton{border:none;}");
    ui->friendrequest->setStyleSheet("QToolButton{border:none;}");
    currentframe->show();
}

void MainWindow::on_chatlist_clicked()
{
    currentframe->hide();
    currentframe = ui->frame2;
    ui->chatlist->setStyleSheet("QToolButton{background-color: rgb(255, 240, 211);\
                                    border:none;border-top:1px solid rgb(219,132,52);border-left:1px solid rgb(219,132,52);\
                                    border-right:1px solid rgb(219,132,52);border-top-left-radius:10px;border-top-right-radius:10px;}");
    ui->friendlist->setStyleSheet("QToolButton{border:none;}");
    ui->friendrequest->setStyleSheet("QToolButton{border:none;}");
    currentframe->show();
}

void MainWindow::on_friendrequest_clicked()
{
    currentframe->hide();
    currentframe = ui->frame3;
    ui->friendrequest->setStyleSheet("QToolButton{background-color: rgb(255, 240, 211);\
                                    border:none;border-top:1px solid rgb(219,132,52);border-left:1px solid rgb(219,132,52);\
                                    border-right:1px solid rgb(219,132,52);border-top-left-radius:10px;border-top-right-radius:10px;}");
    ui->friendlist->setStyleSheet("QToolButton{border:none;}");
    ui->chatlist->setStyleSheet("QToolButton{border:none;}");
    currentframe->show();
}



void addFriendtoList()
{
    //获取已添加好友的头像、用户名
    QString img;

}

void addGrouptoList()
{

}





/*
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int i=1;
    //定义绘制器
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen); //用于轮廓线
    painter.setBrush(QBrush(Qt::gray));  //用于填充

    //QIcon Friendicon = ; //获取头像
    //QPixmap pixmap = Friendicon.pixmap(QSize(20,20));
    QPixmap pixmap = QPixmap(":/img/1.png");

    if(i==1) //用户
    {
        //头像

        painter.drawPixmap(QRect(20,10,40,40),pixmap);

        //框加边
        QColor border1(234, 234, 234);
        painter.setBrush(QBrush(border1));
        painter.drawRoundedRect(80-1, 10+1, 350+2, 40+2, 4, 4);
        //框
        QColor col_Kuang(255,255,255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(80, 10, 350, 40,4,4);

        //内容
        QPen penText;
        penText.setColor(QColor(0, 0, 0));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(QRect(80, 10, 350, 40),"qwqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",option );
        }
    else if(i==2) //自己
    {
            //头像
            painter.drawPixmap(490,10,40,40, pixmap);

            //框
            QColor col_Kuang(75,164,242);
            painter.setBrush(QBrush(col_Kuang));
            painter.drawRoundedRect(80, 10, 350, 40,4,4);


            //内容
            QPen penText;
            penText.setColor(Qt::white);
            painter.setPen(penText);
            QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
            option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
            painter.setFont(this->font());
            QString msg = "m_msg";
            painter.drawText(QRect(80, 10, 350, 40),msg,option);
        }
    else if(i==3) //时间
    {
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MicrosoftYaHei");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(),"m_curTime",option);
    }
}
*/



void MainWindow::onShakeWindow(ChatMessage msg)
{
    //quint32 sender=msg.getSender();
    //QListWidget*q=chatMap[sender];
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

addfriendalert* MainWindow::GetAddfriendalert(){
    if(newWindow == nullptr){
        newWindow = new addfriendalert;
    }
    return newWindow;
}

void MainWindow:: RefreshFriendList(){
    getFriendInfo();
}
addfriend * MainWindow:: GetAddfriend(){
    if(newAddfriend == nullptr){
        newAddfriend = new addfriend;
    }
    return newAddfriend;
}
void MainWindow::RefreshGroupList(){
    GroupList();
}


//鼠标按下
void MainWindow::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}
void MainWindow::opendeveloperModeWidget()
{
    //打开开发者模式
    qDebug()<<"打开开发者模式";
    Widget * w = new Widget();
    w->show();
}
chooseFile * MainWindow::GetChooseFlie(){
    if(cFile == nullptr){
        cFile = new chooseFile;
    }
    return cFile;
}
ChooseImage * MainWindow::GetChooseImage(){
    if(cImag == nullptr){
        cImag = new ChooseImage;
    }
    return cImag;
}
void MainWindow::showReceivedImg(QString Path, FileMeta info){
    QMap<QString,quint32> * tmp = ClientController::GetClientInstance()->GetChatImg();
    if(tmp->contains(info.toQString())){
        showImgMessage(Path,(*tmp)[info.toQString()]);
        tmp->erase(tmp->find(info.toQString()));
    }
}
void MainWindow::showImgMessage(QString img, quint32 receiver)
{
    //假设我收到一张图片img的名字
    QString imgpth = img; //图片完整路径
    qDebug()<<"receiveImg:"<<img;
    //quint32 nowchat=msg.getSender();
    //quint32 nowuserinfo=friendInfo->getid();
    quint32 nowchat=receiver; //发图片者的id
    quint32 nowuserinfo=friendInfo->getid(); //当前聊天好友的id
    if(nowchat==nowuserinfo){
        ItemWidget* item=new ItemWidget(this);
        item->setColor(color);
        int height=item->SetFriendsImg(nowchat,":/img/defaultimg.png",imgpth);
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        pchatw->addItem(line);
        pchatw->setItemWidget(line, item);
        pchatw->scrollToBottom();
    }else{
        QListWidget* nowwidget=chatMap[nowchat];
        ItemWidget* item=new ItemWidget(nowwidget);
        item->setColor(color);
        int height=item->SetFriendsImg(nowchat,":/img/defaultimg.png",imgpth);
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        nowwidget->addItem(line);
        nowwidget->setItemWidget(line, item);
        QToolButton* nowbutton=Mapfriend[nowchat];
        nowbutton->setStyleSheet("background-color:rgb(255,0,0);front-size:20px;");
    };

}

void MainWindow::showFileMessage(ChatMessage chat_msg)
{
    //假设我收到一个文件的名字filename
    FileMeta tmp =FileMeta::fromQByteArray(chat_msg.getContent().toUtf8());
    QString filename = tmp.getBaseName();
    qDebug()<<"receiveFile:" <<filename;
    //quint32 nowchat=msg.getSender();
    //quint32 nowuserinfo=friendInfo->getid();
    quint32 nowchat=chat_msg.getSender(); //发图片者的id
    quint32 nowuserinfo=friendInfo->getid(); //当前聊天好友的id
    if(nowchat==nowuserinfo){
        ItemWidget* item=new ItemWidget(this);
        item->setColor(color);
        int height=item->SetFriendsFile(nowchat,":/img/defaultimg.png",filename,chat_msg);
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        pchatw->addItem(line);
        pchatw->setItemWidget(line, item);
        pchatw->scrollToBottom();
    }else{
        QListWidget* nowwidget=chatMap[nowchat];
        ItemWidget* item=new ItemWidget(nowwidget);
        item->setColor(color);
        int height=item->SetFriendsFile(nowchat,":/img/defaultimg.png",filename,chat_msg);
        QListWidgetItem * line = new QListWidgetItem;
        line->setSizeHint(QSize(350, height));
        nowwidget->addItem(line);
        nowwidget->setItemWidget(line, item);
        QToolButton* nowbutton=Mapfriend[nowchat];
        nowbutton->setStyleSheet("background-color:rgb(255,0,0);front-size:20px;");
    };

}
void MainWindow::showMyImgMessage(QString img, quint32 receiver){
    ItemWidget* item=new ItemWidget(this);
    item->setColor(color);
    int height=item->SetMyImg(receiver,":/img/defaultimg.png",img);
    QListWidgetItem * line = new QListWidgetItem;
    line->setSizeHint(QSize(350, height));
    pchatw->addItem(line);
    pchatw->setItemWidget(line, item);
    pchatw->scrollToBottom();
}
