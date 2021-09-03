#ifndef NEW_WINDOWS_H
#define NEW_WINDOWS_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class new_windows;
}

class new_windows : public QWidget
{
    Q_OBJECT

public:
    explicit new_windows(QWidget *parent = nullptr);
    ~new_windows();
    void SetSend(quint32 send);
    void SetReceive(quint32 receive);
    quint32 GetSend();
    quint32 GetReceive();
private slots:
    void on_pushButton_clicked();//yes
    void on_pushButton_2_clicked();//no
private:
    Ui::new_windows *ui;
    quint32 send;
    quint32 receive;
};

#endif // NEW_WINDOWS_H
