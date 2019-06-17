#include "client.h"
#include "clientsocketmanager.h"
#include <QMessageBox>
#include <QTime>
Client::Client(QObject *parent)
    : QObject(parent),
    loginWidget(new Widget),
    chatWidget(new ChatRoom),
    registerDialog(new registDialog(loginWidget)),
    timer(new QTimer(this))
{
    ClientSocketManager::getInstance()->initSocket();
    const ClientSocket* socket = ClientSocketManager::getInstance()->getCs();

    QObject::connect(loginWidget,SIGNAL(RegistBtn()),SLOT(onRegistBtn()));

    QObject::connect(socket, SIGNAL(registerSuccess(QString)),this, SLOT(onRegisterSuccess(QString)));  //注册成功


    QObject::connect(socket, SIGNAL(registerFailed(QString)),                                   //注册失败
                     this, SLOT(onRegisterFailed(QString)));

    QObject::connect(socket, SIGNAL(loginSuccess(QString,QString)),                             //登陆成功
                     this, SLOT(onLoginSuccess(QString,QString)));

    QObject::connect(socket, SIGNAL(loginFailed(QString)),                                      //登陆失败
                     this, SLOT(onLoginFailed(QString)));

    QObject::connect(socket, SIGNAL(quit()), this, SLOT(onQuit()));                             //退出信号

    QObject::connect(socket, SIGNAL(chat(QString)), chatWidget, SLOT(onChat(QString)));         //聊天包

    QObject::connect(socket, SIGNAL(refreshUser(QStringList)), chatWidget, SLOT(onRefreshUser(QStringList)));   //刷新房间用户

    QObject::connect(socket, SIGNAL(newroom(QString)),chatWidget,SLOT(onnewroom(QString)));

    QObject::connect(socket,SIGNAL(topupsuccess(QString)),SLOT(ontopupsuccess(QString)));

    QObject::connect(socket,SIGNAL(topupfalse(QString)),SLOT(ontopupfalse(QString)));

    QObject::connect(socket,SIGNAL(updateUser(int)),chatWidget,SLOT(onupdateUser(int)));

    QObject::connect(socket,SIGNAL(startLiveUser()),chatWidget,SLOT(onstartLiveUser()));

    QObject::connect(socket,SIGNAL(quitLiveUser(QString)),chatWidget,SLOT(onquitLiveHandler(QString)));

    QObject::connect(socket,SIGNAL(danmu(QString)),chatWidget,SLOT(ondanmu(QString)));

    QObject::connect(socket,SIGNAL(rocket()),chatWidget,SLOT(onrocket()));
    QObject::connect(socket,SIGNAL(plane()),chatWidget,SLOT(onplane()));
    QObject::connect(socket,SIGNAL(lunchuan()),chatWidget,SLOT(onlunchuan()));
    QObject::connect(socket,SIGNAL(yuchi()),chatWidget,SLOT(onyuchi()));
}

Client::~Client()
{
    delete loginWidget;
    delete chatWidget;

}

void Client::onRegisterSuccess(QString message)
{
    QMessageBox::information(loginWidget,"注册信息",message);
    QPropertyAnimation* a = new QPropertyAnimation(registerDialog,"windowOpacity");
    a->setDuration(1500);
    a->setStartValue(1);
    a->setEndValue(0);
    a->start();
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    loginWidget->show();
}

void Client::onRegisterFailed(QString message)
{
    QMessageBox::warning(loginWidget,"注册信息",message);
}

void Client::onLoginSuccess(QString username, QString message)
{
    QMessageBox::information(loginWidget, "登录信息", message);

    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    loginWidget->hide();

    QTime dietime = QTime::currentTime().addMSecs(200);
    while(QTime::currentTime() < dietime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }

    chatWidget->setUsername(username);

    QPropertyAnimation* a = new QPropertyAnimation(chatWidget,"windowOpacity");

    a->setDuration(1500);
    a->setStartValue(0);
    a->setEndValue(1);
    a->start();
    chatWidget->show();

}

void Client::onLoginFailed(QString message)
{
    QMessageBox::warning(loginWidget,"登陆信息",message);
}

void Client::onQuit()
{
    QPropertyAnimation* b = new QPropertyAnimation(chatWidget,"windowOpacity");
    b->setDuration(1000);
    b->setStartValue(1);
    b->setEndValue(0);
    b->start();
    chatWidget->hide();

    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    loginWidget->show();
}

void Client::onRegistBtn()
{
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    loginWidget->hide();
    QPropertyAnimation* b = new QPropertyAnimation(registerDialog,"windowOpacity");
    b->setDuration(1000);
    b->setStartValue(0);
    b->setEndValue(1);
    b->start();
    registerDialog->show();
}

void Client::ontopupfalse(QString message)
{
    QMessageBox::warning(loginWidget,"充值信息",message);
}

void Client::ontopupsuccess(QString message)
{
    QMessageBox::information(loginWidget,"充值信息",message);
    //成功这里需要更新金额
    //chatwidget.set    获取新的余额

}



