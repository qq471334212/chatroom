#ifndef CLIENT_H
#define CLIENT_H
#include "widget.h"
#include "chatroom.h"
#include <QObject>
#include "registdialog.h"
#include "topupdialog.h"
#include <QUdpSocket>
#include "camerawidget.h"
#include <QPropertyAnimation>
#include <QTimer>
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    virtual ~Client();
    void show(){
        animation= new QPropertyAnimation(loginWidget,"windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        loginWidget->show();

    }

signals:

public slots:
    void onRegisterSuccess(QString message);
    void onRegisterFailed(QString message);
    void onLoginSuccess(QString username, QString message);
    void onLoginFailed(QString message);
    void onQuit();
    void onRegistBtn();
    void ontopupfalse(QString);
    void ontopupsuccess(QString);
private:
    Widget* loginWidget;
    ChatRoom* chatWidget;
    registDialog* registerDialog;
    //cameraWidget* camerawidget;
    QPropertyAnimation *animation;
    QTimer* timer;
};

#endif // CLIENT_H
