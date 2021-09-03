#include "widget.h"
#include "ui_widget.h"
#include "servercontroller.h"
#include "Utilities/utilities.h"
#include "DataBase/datadb.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ServerController::getServerInstance()->start(9999);
    ServerController::getResServerInstance()->start(6666);

    //获得日志并写入
    connect(Log::GetLogObj(), &Log::readyShowLog, this, &Widget::showLog);
    //自动滚动日志区域
    connect(ui->textBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
    DataDB::GetInstance();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showLog(QString str){
    ui->textBrowser->append(str);
}

void Widget::autoScroll() {
    QTextCursor cursor =  ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cursor);
}
