#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class alarmWidget;
}

class alarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit alarmWidget(QWidget *parent = nullptr);
    ~alarmWidget();
    void setLabel(QString str);

private slots:
    void closeAlarm();

private:
    Ui::alarmWidget *ui;
    QLabel* lab;
};

#endif // ALARMWIDGET_H
