#ifndef STANDARDDATETIMEUTILITIES_H
#define STANDARDDATETIMEUTILITIES_H
#include <QDateTime>

//提供标准时间格式的获取 code by BFZD

class StdDatetimeUtilities:public QDateTime
{
public:
    explicit StdDatetimeUtilities(QDateTime *parent = nullptr);
    static QString GetDateTime(){
        return (QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss");
    }
    static QString GetDateTimeWithNoSpace(){
        return (QDateTime::currentDateTime()).toString("yyyy_MM_dd_hh_mm_ss_ms");
    }
};

#endif // STANDARDDATETIMEUTILITIES_H
