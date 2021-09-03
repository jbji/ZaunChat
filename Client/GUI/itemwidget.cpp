#include "itemwidget.h"
#include "ui_itemwidget.h"
#include <QDebug>
#include <QToolButton>
#include "Controller/clientcontroller.h"
#include "DataModel/chatmessage.h"

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("QWidget{background-color:rgba(255,255,255,0);border:none;}");
    countLine = 0;
    FIle = ChatMessage(0,0,"");
    color = "rgb(254,208,142)";
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

void ItemWidget::setColor(QString c)
{
    color = c;
}
int ItemWidget::SetMyData(quint32 id, QString picon, QString txt)
{
    //头像
    QToolButton* imgbtn = new QToolButton(this);
    imgbtn->setIcon(QIcon(picon));
    imgbtn->setIconSize(QSize(40,40));
    imgbtn->setGeometry(500,10,40,40);
    imgbtn->setStyleSheet("QToolButton:{border:none;}");
    imgbtn->show();

    QFontMetrics fm(this->font());

    //id
    QLabel* idlab = new QLabel(this);
    idlab->setText(QString::number(id));
    idlab->setGeometry(480-fm.horizontalAdvance(QString::number(id)),10,fm.horizontalAdvance(QString::number(id)),fm.height());

    //文本
    QLabel* txtlab = new QLabel(this);
    txtlab->setStyleSheet("QLabel{background-color:"+color+";border:5px solid "+color+";\
                              border-top-left-radius:15px;\
                              border-bottom-left-radius:15px;\
                              border-bottom-right-radius:15px;}");
    int txtheight = fm.height();
    countLine = 0;
    longestWidth = 0;
    txt = Splite(txt,fm);
    qDebug()<<countLine;
    txtlab->setText(txt);
    txtlab->setGeometry(480-longestWidth-30, 30, longestWidth+30, txtheight*countLine+40);
    txtlab->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    txtlab->setWordWrap(true);
    return 30+10+txtheight*countLine+40;
}

int ItemWidget::SetFriendsData(quint32 id, QString picon, QString txt)
{
    //头像
    QToolButton* imgbtn = new QToolButton(this);
    imgbtn->setIcon(QIcon(picon));
    imgbtn->setIconSize(QSize(40,40));
    imgbtn->setGeometry(10,10,40,40);
    imgbtn->setStyleSheet("QToolButton:{border:none;}");
    imgbtn->show();

    QFontMetrics fm(this->font());

    //id
    QLabel* idlab = new QLabel(this);
    idlab->setText(QString::number(id));
    idlab->setGeometry(70,10,fm.horizontalAdvance(QString::number(id))+20,fm.height());

    //文本
    QLabel* txtlab = new QLabel(this);
    txtlab->setStyleSheet("QLabel{background-color:rgb(255,255,255);border:2px solid "+color+";\
                            border-top-right-radius:15px;\
                            border-bottom-left-radius:15px;\
                            border-bottom-right-radius:15px}");
    int txtheight = fm.height();
    countLine = 0;
    longestWidth = 0;
    countLine = 0;
    txt = Splite(txt,fm);
    qDebug()<<countLine;
    txtlab->setText(txt);
    txtlab->setGeometry(70, 30, longestWidth+30, txtheight*countLine+35);
    txtlab->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    txtlab->setWordWrap(true);
    return 30+10+txtheight*countLine+35;
}

QString ItemWidget::Splite(QString txt, QFontMetrics& font)
{
    int txtwidth = txt.size(); //当前字符串长度
    qDebug()<<txt.indexOf("\n");
    if(txt.indexOf("\n") != -1)
    {
        QString qstrLeftData = txt.left(txt.indexOf("\n"));
        qDebug()<<qstrLeftData;
        QString qstrMidData = txt.mid(txt.indexOf("\n")+1);
        qDebug()<<qstrMidData;
        return Splite(qstrLeftData, font) + "\n" + Splite(qstrMidData, font);
    }
    int txtwidth2 = font.horizontalAdvance(txt); //当前字符串所占像素长度
    //qDebug()<<txtwidth;
    qDebug()<<txtwidth2;
    if(txtwidth2<=200)  //不需要继续划分
    {
        countLine++;
        if(txtwidth2>longestWidth)
            longestWidth = txtwidth2;
        qDebug()<<longestWidth;
        return txt;
    }
    else
    {
        countLine++;
        longestWidth = 200;
        QString qstrLeftData = txt.left(txtwidth*200/txtwidth2);
        qDebug()<<qstrLeftData;
        QString qstrMidData = txt.mid(txtwidth*200/txtwidth2);
        qDebug()<<qstrMidData;
        return qstrLeftData + "\n" + Splite(qstrMidData, font);
    }
}
int ItemWidget::SetMyImg(quint32 id,QString picon ,QString imgpth)
{
    //头像
    QToolButton* imgbtn = new QToolButton(this);
    imgbtn->setIcon(QIcon(picon));
    imgbtn->setIconSize(QSize(40,40));
    imgbtn->setGeometry(500,10,40,40);
    imgbtn->setStyleSheet("QToolButton:{border:none;}");
    imgbtn->show();

    QFontMetrics fm(this->font());

    //id
    QLabel* idlab = new QLabel(this);
    idlab->setText(QString::number(id));
    idlab->setGeometry(480-fm.horizontalAdvance(QString::number(id)),10,fm.horizontalAdvance(QString::number(id)),fm.height());

    //图片
    QToolButton* img = new QToolButton(this);
    img->setStyleSheet("QToolButton{border:none}");
    img->setToolButtonStyle(Qt::ToolButtonIconOnly);
    img->setIcon(QIcon(imgpth));
    QImage* pimg = new QImage(imgpth);
    int width = 150;
    int height = 150*pimg->height()/pimg->width();
    img->setIconSize(QSize(width,height));
    img->setGeometry(480-width-30, 32, width+30, height+35);
    //connect(img,SIGNAL(clicked()),this,SLOT(downloadImg()));//点击图片可以下载图片
    return 30+10+height+35;
}

int ItemWidget::SetFriendsImg(quint32 id,QString picon ,QString imgpth)
{
    //头像
    QToolButton* imgbtn = new QToolButton(this);
    imgbtn->setIcon(QIcon(picon));
    imgbtn->setIconSize(QSize(40,40));
    imgbtn->setGeometry(10,10,40,40);
    imgbtn->setStyleSheet("QToolButton:{border:none;}");
    imgbtn->show();

    QFontMetrics fm(this->font());

    //id
    QLabel* idlab = new QLabel(this);
    idlab->setText(QString::number(id));
    idlab->setGeometry(70,10,fm.horizontalAdvance(QString::number(id))+20,fm.height());

    //图片
    QToolButton* img = new QToolButton(this);
    img->setStyleSheet("QToolButton{border:none}");
    img->setToolButtonStyle(Qt::ToolButtonIconOnly);
    img->setIcon(QIcon(imgpth));
    QImage* pimg = new QImage(imgpth);
    int width = 150;
    int height = 150*pimg->height()/pimg->width();
    img->setIconSize(QSize(width,height));
    img->setGeometry(70, 32, width+30, height+35);
    //connect(img,SIGNAL(clicked()),this,SLOT(downloadImg()));//点击图片可以下载图片
    return 30+10+height+35;
}
int ItemWidget::SetFriendsFile(quint32 id,QString picon,QString Filename,ChatMessage chat_msg)
{
    //头像
    QToolButton* imgbtn = new QToolButton(this);
    imgbtn->setIcon(QIcon(picon));
    imgbtn->setIconSize(QSize(40,40));
    imgbtn->setGeometry(10,10,40,40);
    imgbtn->setStyleSheet("QToolButton:{border:none;}");
    imgbtn->show();

    QFontMetrics fm(this->font());

    //id
    QLabel* idlab = new QLabel(this);
    idlab->setText(QString::number(id));
    idlab->setGeometry(70,10,fm.horizontalAdvance(QString::number(id))+20,fm.height());

    //文本
    filename = Filename;
    QToolButton* File = new QToolButton(this);
    File->setText(Filename);
    File->setStyleSheet("QToolButton{text-decoration:underline;\
                            background-color:rgb(255,255,255);border:2px solid "+color+";\
                            border-top-right-radius:15px;\
                            border-bottom-left-radius:15px;\
                            border-bottom-right-radius:15px}");
    File->setToolButtonStyle(Qt::ToolButtonIconOnly);
    int txtheight = fm.height();
    File->setGeometry(70, 32, fm.horizontalAdvance(Filename)+30, txtheight+35);
    FIle = chat_msg;
    connect(File,SIGNAL(clicked()),this,SLOT(downloadFile()));//点击文件可以下载
    return 30+10+txtheight+35;
}
void ItemWidget::downloadFile()
{
    ClientController::GetClientInstance()->requestFileByRawMsg(FIle);
}
