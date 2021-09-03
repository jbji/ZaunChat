#include "log.h"

#include "utilities.h"

Log::Log(QObject *parent) : QObject(parent)
{

}

Log * Log::log_obj = nullptr;

Log * Log::GetLogObj(){
    if(!log_obj){
        log_obj = new Log();
    }
    return log_obj;
}

void Log::writeLog(QString log_str){
    emit readyShowLog(StdDatetimeUtilities::GetDateTime() + " " + log_str);
}
