#include "servercontroller.h"

Server* ServerController::_server = NULL;

ServerController::ServerController()
{
}

Server* ServerController::getServerInstance()
{
    if(_server == NULL)
    {
        _server = new Server;
    }
    return _server;
}
TcpClientSocket* ServerController::GetClient(quint32 Id){
    return getServerInstance()->getClients(Id);
}


ResServer* ServerController::_resServer = nullptr;

ResServer *  ServerController::getResServerInstance()
{
    if(!_resServer)
    {
        _resServer = new ResServer;
    }
    return _resServer;
}
