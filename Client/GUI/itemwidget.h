#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include "DataModel/chatmessage.h"
namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = nullptr);
    ~ItemWidget();

    int SetMyData(quint32 id, QString picon, QString txt); //用户消息框
    int SetFriendsData(quint32 id,QString picon, QString txt); //用户消息框
    void setColor(QString c);
    int SetMyImg(quint32 id,QString picon ,QString imgpth);
    int SetFriendsImg(quint32 id,QString picon ,QString imgpth);
    int SetFriendsFile(quint32 id,QString picon,QString Filename,ChatMessage chat_msg);

private slots:
    void downloadFile();
private:
    Ui::ItemWidget *ui;
    QString Splite(QString txt, QFontMetrics& font);
    int countLine;
    int longestWidth;
    QString color; //气泡颜色
    ChatMessage FIle;
    QString filename;
};

#endif // ITEMWIDGET_H
