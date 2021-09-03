#include "ressocket.h"

#include "DataModel/datamodel.h"

#include <QFile>
#include <QtNetwork>
#include "Utilities/log.h"
#include "Network/ResAssist/localcache.h"

#include "servercontroller.h"

ResSocket::ResSocket(QObject *parent) : TcpClientSocket(parent)
{

}


void ResSocket::receiveMessage()
{
    Log::GetLogObj()->writeLog("[ResSocket Receive Message] buffering Res");

    QDataStream in(this);

    //取得消息的大小
    if(_blockSize == 0){
        if(bytesAvailable() < (int)sizeof(quint32) ){
            return;
        }
        in >> _blockSize;
    }

    //取得剩余没有读取部分的大小, 如果剩余部分过小 则退出后等待下次读取
    quint32 remainingSize = bytesAvailable();
    if(remainingSize < _blockSize){
        return;
    }

    //读取消息
    quint32 head;
    in >> head;
    if(head == Msg::msgHead){
        _blockSize = _blockSize - sizeof(quint32);
        QByteArray buf;
        buf.reserve(_blockSize);
        //曲线救国
        while(_blockSize > 0){
            quint8 tmp;
            in >> tmp;
            buf.append(tmp);
            _blockSize -= 1;
        }
        Msg tmp = Msg::fromQByteArray(buf);
        //服务端收到请求文件的消息
        if(tmp.getType() == MsgType::RES_REQUEST_IMG){
            Log::GetLogObj()->writeLog("正在处理获取图片请求");
            FileMeta filemeta = FileMeta::fromQByteArray(tmp.getContent());
            if(LocalCache::GetInstance()->isExistImg(filemeta.getUniqueName())){
                QString absolutePath = "./cache/images/" + filemeta.getUniqueName();
                QFile file(absolutePath);
                file.open(QIODevice::ReadOnly);
                QByteArray block = file.readAll();
                file.close();
                //上传文件
                Msg tmp = Msg(MsgType::RES_IMG, FilePackage(filemeta, block).toQByteArray());
                sendMessage(&tmp);
            }
            return;
        }
        if(tmp.getType() == MsgType::RES_REQUEST_FILE){
            Log::GetLogObj()->writeLog("正在处理获取文件请求");
            FileMeta filemeta = FileMeta::fromQByteArray(tmp.getContent());
            if(LocalCache::GetInstance()->isExistFile(filemeta.getUniqueName())){
                Log::GetLogObj()->writeLog("服务端存在文件");
                QString absolutePath = "./cache/files/" + filemeta.getUniqueName();
                QFile file(absolutePath);
                file.open(QIODevice::ReadOnly);
                QByteArray block = file.readAll();
                file.close();
                //上传文件
                Msg tmp = Msg(MsgType::RES_FILE, FilePackage(filemeta, block).toQByteArray());
                sendMessage(&tmp);
            }
            return;
        }
        //从客户端接收传来的文件
        FilePackage pack = FilePackage::fromQByteArray(tmp.getContent());
        FileMeta filemeta = pack.getInfo();
        QString path;
        QDir *folder = new QDir;
        if(tmp.getType() == MsgType::RES_FILE){
            if(!folder->exists("./cache/files")){
                folder->mkpath("./cache/files");
            }//I like ----by BFZD
            path = "./cache/files/" + filemeta.getUniqueName();
        }
        if(tmp.getType() == MsgType::RES_IMG){
            if(!folder->exists("./cache/images")){
                folder->mkpath("./cache/images");
            }//but I don't :( ---by jbji
            path = "./cache/images/" + filemeta.getUniqueName();
        }
        if(tmp.getType() == MsgType::RES_IMG
                || tmp.getType() == MsgType::RES_FILE){
            QFile file_local(path);
            if(file_local.open(QIODevice::WriteOnly)){
                Log::GetLogObj()->writeLog("ResSocket:: File Written ALL RIGHT!");
                file_local.write(pack.getContent());
                file_local.close();
                Log::GetLogObj()->writeLog("ResSocket sender:" + QString::number(pack.getSender()) + "recver:" + QString::number(pack.getReceiver()));
                if(pack.getSender() != 0 && pack.getReceiver() != 0){
                    Log::GetLogObj()->writeLog("ResSocket sender:" + QString::number(pack.getSender()) + "recver:" + QString::number(pack.getReceiver()));
                    Log::GetLogObj()->writeLog("Res: " + QString::number(pack.getSender()) + " to " + QString::number(pack.getReceiver()));
                    TcpClientSocket * tmpClient = ServerController::GetClient(pack.getReceiver());
                    if(tmpClient){
                        tmpClient->sendMessage(new Msg(
                                             (tmp.getType() == MsgType::RES_IMG ? MsgType::MSG_PIC : MsgType::MSG_FILE)
                                             , ChatMessage(
                                                     pack.getSender(), pack.getReceiver(), filemeta.toQString()
                                                     ).toQByteArray()
                                                 ));
                    }
                }
            }
        }

    }

    _blockSize = 0;
    if(bytesAvailable() > 0){
        this->receiveMessage();
    }
}


