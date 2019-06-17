#include "clientsocket.h"
#include <QHostAddress>
#include "protocol.h"
#include <QDateTime>
#include <QJsonArray>
#include <QDebug>
ClientSocket::ClientSocket(QTcpSocket* socket,QObject *parent)
    :QObject(parent),
      socket(socket),
      timer(new QTimer(this))
{
    if(this->socket == nullptr){
        this->socket = new QTcpSocket(this);
    }


    QObject::connect(this->socket,SIGNAL(disconnect()),SLOT(ondisconnect()));
    QObject::connect(timer,SIGNAL(timeout()),SLOT(onConnectToHost()));
    QObject::connect(this->socket,SIGNAL(connected()),SLOT(onconnected()));
    QObject::connect(this->socket,SIGNAL(readyRead()),SLOT(onReadyRead()));
    if(!this->socket->isValid()){
        timer->start(2000);
    }
}

void ClientSocket::ondisconnect()   //不在线时启动重连功能
{
    timer->start(2000);
}

void ClientSocket::onConnectToHost()
{
    socket->connectToHost(QHostAddress("127.0.0.1"),10005);
}

void ClientSocket::onconnected()
{
    timer->stop();
}

void ClientSocket::onReadyRead()
{
    buf += socket->readAll();   //持续不断的读取字节流到buf中

    while (1) {
        QPair<bool,Protocol> data = Protocol::unpack(buf);

        if(data.first == false) return;
        Protocol& p = data.second;
        switch (p.getType()) {
        case Protocol::quitLive:
            this->quitLiveHandler(p);
            break;
        case Protocol::startLive:
            this->startLive();
            break;
        case Protocol::updatemoney:
            this->updateHandler(p);
            break;
        case Protocol::topup:
            this->topupHandler(p);
            break;
        case Protocol::refreshUser:
            this->refreshUserHandler(p);
            break;
        case Protocol::chat:
            this->chatHandler(p);
            break;
        case Protocol::quit:
            this->quitHandler(p);
            break;
        case Protocol::gift:
            this->giftHandler(p);
            break;
        case Protocol::login:
            this->loginHandler(p);
            break;
        case Protocol::regist:
            this->registHandler(p);
            break;
        case Protocol::none:
            break;
        case Protocol::newroom:
            this->newroomHandler(p);
            break;
        case Protocol::goroom:
            break;
        }
    }
}



void ClientSocket::registHandler(const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "success"){
        emit registerSuccess(protocol["message"].toString());
    }else{
        emit registerFailed(protocol["message"].toString());
    }
}

void ClientSocket::loginHandler(const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "success"){
        emit loginSuccess(protocol["username"].toString(),protocol["message"].toString());
    }else if (type == "failed") {
        emit loginFailed(protocol["message"].toString());
    }else{}
}

void ClientSocket::quitHandler(const Protocol &protocol)
{
    Q_UNUSED(protocol);
    emit quit();

}

void ClientSocket::giftHandler(const Protocol &protocol)
{
    int money = protocol["money"].toInt();
    if(money == 500){
        emit rocket();
    }else if(money == 100){
        emit plane();
    }else if (money == 50) {
        emit lunchuan();
    }else if (money ==10) {
        emit yuchi();
    }else {
        return;
    }
}

void ClientSocket::chatHandler(const Protocol &protocol)
{
    QString buf = protocol["username"].toString();
    buf += " ";
    buf += QDateTime::currentDateTime().toString();
    buf += ":\n";
    buf += protocol["chat"].toString();

    emit danmu(protocol["chat"].toString());
    emit chat(buf);

}

void ClientSocket::refreshUserHandler(const Protocol &protocol)     //
{
    QJsonArray array = protocol["user"].toArray();
    QStringList list;
    for(int i = 0;i<array.size();i++)
            list.append(array[i].toString());
    emit refreshUser(list);
}

void ClientSocket::newroomHandler(const Protocol &protocol)
{
    QString text = protocol["newroom"].toString();
    qDebug() << text;
    emit newroom(text);
}

void ClientSocket::topupHandler(const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "success"){
        emit topupsuccess(protocol["message"].toString());
    }else if(type == "false"){
        emit topupfalse(protocol["message"].toString());
    }
}

void ClientSocket::updateHandler(const Protocol &protocol)
{
    int money = protocol["money"].toInt();
    emit updateUser(money);
}

void ClientSocket::startLive()
{
    emit startLiveUser();
}

void ClientSocket::quitLiveHandler(const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    QString text;
    if(type == "success"){
        text = "开启直播";
    }else{
        text = "观看直播";
    };
    emit quitLiveUser(text);
}

