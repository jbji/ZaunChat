#include "ressocket.h"

#include "Utilities/utilities.h"
#include "Controller/clientcontroller.h"
#include <QtNetwork>
#include "localcache.h"

ResSocket::ResSocket(QObject *parent) :
    TcpClientSocket(parent)
{
    ConnectToServer();
}

ResSocket*  ResSocket::socket = NULL;


void ResSocket::AbortConnection(){
    GetSocket()->abort();
}

ResSocket*  ResSocket::GetSocket() {
    if (socket == NULL) {
        socket = new ResSocket();
    }
    return socket;
}


void ResSocket::ConnectToServer() {

    setServerIP(ClientController::GetServerIP());
    setServerTcpPort("6666");
    if (!connectToServer()) {
        Log::GetLogObj()->writeLog("[ResSocket: connectToServer] Connection Failed.");
    }else {
        Log::GetLogObj()->writeLog("[ResSocket: connectToServer] Connection Successful.");
    }
}

//RES_REQUEST_IMG, RES_REQUEST_FILE,  RES_IMG,   RES_FILE

void ResSocket::receiveMessage(){

    Log::GetLogObj()->writeLog("[ResSocket Receiver Message] buffering Res");
    emit receivingThings();

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
        //从服务端接收传来的文件
        FilePackage pack = FilePackage::fromQByteArray(tmp.getContent());
        FileMeta filemeta = pack.getInfo();
        QString path;
        QDir *folder = new QDir;
        if(tmp.getType() == MsgType::RES_FILE){
            if(!folder->exists("./cache/files")){
                folder->mkpath("./cache/files");
            }//I like ----by BFZD
            path = "./cache/files/" + filemeta.getBaseName() + "_" + filemeta.getUniqueName();
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
                file_local.write(pack.getContent());
                file_local.close();
                LocalCache::GetInstance()->broadcastReceivedRes(tmp.getType(), filemeta);
            }
        }
    }

    _blockSize = 0;
    if(bytesAvailable() > 0){
        this->receiveMessage();
    }
}
