#include "clientsocketmanager.h"

ClientSocketManager::ClientSocketManager()
    : cs(nullptr)
{

}

ClientSocket *ClientSocketManager::getCs() const
{
    return cs;
}
ClientSocketManager* ClientSocketManager::instance = new ClientSocketManager;
