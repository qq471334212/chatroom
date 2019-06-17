#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include <QCloseEvent>
#include <QListWidgetItem>
#include "topupdialog.h"
#include "camerawidget.h"
namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    QString getUsername() const;
    void setUsername(const QString &value);

public slots:
    void onChat(QString data);
    void ondanmu(QString text);

private slots:
    void on_leinput_returnPressed();
    void on_inputbtn_clicked();
    void onRefreshUser(QStringList list);
    void on_quitbtn_clicked();
    void on_pushButton_clicked();
    void onnewroom(QString roomname);
    void on_pushButton_2_clicked();
    void on_chatroom_itemDoubleClicked(QListWidgetItem *item);
    void ontopup_1(int);
    void onupdateUser(int);
    void on_pushButton_3_clicked();
    void on_startinput_clicked();
    void onstartLiveUser();
    void onquitLiveHandler(QString);
    void on_rocket_clicked();
    void on_flower_clicked();
    void on_good_clicked();
    void on_FbBtn_clicked();
    //弹幕槽函数
    void onrocket();
    void onplane();
    void onlunchuan();
    void onyuchi();

protected:
    virtual void closeEvent(QCloseEvent* event);
    //bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::ChatRoom *ui;
    QString username;       //当前用户的名字
    QString roomname_;      //房间名
    TopupDialog* topupD;
    cameraWidget* cameraW;
    //QLabel* label;

};

#endif // CHATROOM_H
