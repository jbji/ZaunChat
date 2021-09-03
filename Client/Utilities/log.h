#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QDebug>

//产生日志

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);

    static Log * GetLogObj();
    void writeLog(QString log);
signals:
    void readyShowLog(QString log);
private:
    static Log * log_obj;
};

#endif // LOG_H
