#include "alarmwidget.h"
#include "ui_alarmwidget.h"

#include <QTimer>

alarmWidget::alarmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarmWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    lab = new QLabel(this);
    lab->setText("");
    lab->setGeometry(10,25,180,50);
    lab->setWordWrap(true);
    lab->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

    QTimer* timer = new QTimer(this);
    timer->start(1000);//时间1秒
    timer->setSingleShot(true);//仅触发一次
    connect(timer, SIGNAL(timeout()), this, SLOT(closeAlarm()));
}

void alarmWidget::closeAlarm()
{
    this->close();
}

alarmWidget::~alarmWidget()
{
    delete ui;
}

void alarmWidget::setLabel(QString str)
{
    lab->setText(str);
}
