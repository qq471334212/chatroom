#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "protocol.h"
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket = nullptr,QObject *parent = nullptr);
    inline quint64 write(QByteArray array){
        return socket->write(array);
    }
    inline bool isValid()const{return socket->isValid();}
signals:
    void sendMessage(QString);
    void registerSuccess(QString);
    void registerFailed(QString);
    void topupsuccess(QString);
    void topupfalse(QString);
    void loginSuccess(QString, QString);
    void loginFailed(QString);
    void newroom(QString);
    void quit();
    void chat(QString);
    void refreshUser(QStringList);
    void updateUser(int);
    void startLiveUser();
    void quitLiveUser(QString);
    void danmu(QString);

    void rocket();
    void plane();
    void lunchuan();
    void yuchi();
public slots:
    void ondisconnect();
    void onConnectToHost();
    void onconnected();
    void onReadyRead();
private:
    QTcpSocket* socket;
    QTimer* timer;
    QByteArray buf;
    void registHandler(const Protocol& protocol);
    void loginHandler(const Protocol& protocol);
    void quitHandler(const Protocol& protocol);
    void giftHandler(const Protocol& protocol);
    void chatHandler(const Protocol& protocol);
    void refreshUserHandler(const Protocol& protocol);
    void newroomHandler(const Protocol& protocol);
    void topupHandler(const Protocol& protocol);
    void updateHandler(const Protocol& protocol);
    void startLive();
    void quitLiveHandler(const Protocol &protocol);
};

#endif // CLIENTSOCKET_H
