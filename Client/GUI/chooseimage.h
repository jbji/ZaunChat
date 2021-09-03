#ifndef CHOOSEIMAGE_H
#define CHOOSEIMAGE_H

#include <QWidget>
#include "user.h"
namespace Ui {
class ChooseImage;
}

class ChooseImage : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseImage(QWidget *parent = nullptr);
    ~ChooseImage();
    void setFriendInfo(User * Friend);
private slots:
    void on_chooseImg_clicked();

    void on_cancelButton_clicked();

    void on_sendImg_clicked();
signals:
    void readyShowMyIMG(QString path,quint32 id);
private:
    Ui::ChooseImage *ui;
    User * friendInfo;
};

#endif // CHOOSEIMAGE_H
