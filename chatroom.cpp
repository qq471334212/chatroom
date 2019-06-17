#include "chatroom.h"
#include "ui_chatroom.h"
#include "protocol.h"
#include "clientsocketmanager.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom),
    topupD(new TopupDialog),
    cameraW(new cameraWidget)
{
//    label = new QLabel;
//    label->resize(120,30);
//    label->setText("创建房间");

    //ui->pushButton_2->installEventFilter(this);

    cameraW->setWindowFlag(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    roomname_ = "Lobby";
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(roomname_);
    ui->chatroom->addItem(item);


    QImage _image;
    _image.load(":/new/prefix1/image/21358791_095926150031_2.jpg");
    setAutoFillBackground(true);
    QPalette pal(palette());
        pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(),
                            Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation)));
    setPalette(pal);

    QObject::connect(topupD,SIGNAL(topup(int)),SLOT(ontopup_1(int)));
}


ChatRoom::~ChatRoom()
{
    delete ui;
    delete topupD;
    delete cameraW;
//    delete label;
}

QString ChatRoom::getUsername() const
{
    return username;
}

void ChatRoom::setUsername(const QString &value)
{
    username = value;
}


//bool ChatRoom::eventFilter(QObject *watched, QEvent *event)
//{
//    if(ui->pushButton_2 == watched){            //给对象按钮安装过滤器
//        if(QEvent::Enter == event->type()){     //事件类型为鼠标进入
//            if(label->isHidden()){
//                QPoint p = ui->pushButton_2->pos();
//                label->move(p.x()+20,p.y()-20);
//                label->show();
//                label->raise();
//                return true;
//            }else{}
//        }else if(QEvent::Leave == event->type()){
//            if(!label->isHidden()){
//                label->hide();
//                return true;
//            }
//        }
//    }

//    return QWidget::eventFilter(watched, event);
//}



void ChatRoom::onChat(QString data)
{
    ui->techat->append(data);
}

void ChatRoom::ondanmu(QString text)
{
    if(cameraW->isHidden()){
        return;
    }else{
        cameraW->onsigBs(text);
    }
}

void ChatRoom::on_leinput_returnPressed()   //确认发送
{
    QString text = ui->leinput->text();
    ui->leinput->clear();
    Protocol p;
    p.setType(Protocol::chat);
    p["roomname"] = roomname_;
    p["username"] = username;
    p["chat"] = text;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_inputbtn_clicked()            //文本输入
{
    QString text = ui->leinput->text();
    ui->leinput->clear();
    Protocol p;
    p.setType(Protocol::chat);
    p["roomname"] = roomname_;
    p["username"] = username;
    p["chat"] = text;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::onRefreshUser(QStringList list)
{
    ui->lwUser->clear();
    ui->lwUser->addItems(list);
}

void ChatRoom::closeEvent(QCloseEvent *event)
{
    if(ClientSocketManager::getInstance()->isValid()){
        event->ignore();
    }else{
        event->accept();
        return;
    }
    Protocol p;
    p.setType(Protocol::quit);
    p["username"] = username;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_quitbtn_clicked()         //退出按钮
{
    Protocol p;
    p.setType(Protocol::quit);
    p["username"] = username;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_pushButton_clicked()  //按钮槽函数,跳出充值界面
{
    //金币充值
    topupD->show();

}

void ChatRoom::onnewroom(QString roomname)              //创建新房间
{
    QListWidgetItem* item_1 = new QListWidgetItem;
    item_1->setText(roomname);
    ui->chatroom->addItem(item_1);
}

void ChatRoom::on_pushButton_2_clicked()            //创建新房间
{
    if(ui->lineEdit_2->text().isEmpty()){
        return;
    }
    //这里有个问题    房间的重复性  房间重名,后面的房间会跳过
    //发包
    Protocol p;
    p.setType(Protocol::newroom);
    p["newroom"] = ui->lineEdit_2->text();
    p["ownername"] = username;
    ui->lineEdit_2->clear();
    ClientSocketManager::getInstance()->write(p.toByteArray());
}


void ChatRoom::on_chatroom_itemDoubleClicked(QListWidgetItem *item) //进入其他房间
{
    Protocol p;
    p.setType(Protocol::goroom);
    p["oldroom"] = this->roomname_;
    if(this->roomname_ == item->text()){
        return;
    }
    this->roomname_ = item->text();
    p["roomname"] = item->text();
    p["username"] = username;
    ClientSocketManager::getInstance()->write(p.toByteArray());

}

void ChatRoom::ontopup_1(int money)     //充值
{
    Protocol p;
    p.setType(Protocol::topup);
    p["money"] = money;
    p["username"] = username;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::onupdateUser(int money)              //
{
    ui->label_4->setText(QString::number(money));
}

void ChatRoom::on_startinput_clicked()      //开启直播按钮
{

    this->cameraW->show();
    //设置这个窗口的房间名和用户名
    cameraW->setRoomname(roomname_);
    cameraW->setUsername(username);

    if(ui->startinput->text() == "开启直播"){
        cameraW->startResponded();
        //发送一个包更改其他用户的按钮
        Protocol p;
        p.setType(Protocol::startLive);
        p["username"] = username;
        p["roomname"] = roomname_;
        p["ownname"] = username;
        ClientSocketManager::getInstance()->write(p.toByteArray());
    }else if(ui->startinput->text() == "观看直播"){
    }else{}

}

void ChatRoom::onstartLiveUser()
{
    ui->startinput->setText("观看直播");
}

void ChatRoom::onquitLiveHandler(QString text)
{
    ui->startinput->setText(text);
    if(text == "开启直播"){
        cameraW->stopResponded();
    }
    cameraW->hide();
}
void ChatRoom::on_pushButton_3_clicked()        //更新金币
{
    Protocol p;
    p.setType(Protocol::updatemoney);
    p["username"] = username;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}
void ChatRoom::on_rocket_clicked()  //送火箭
{
    this->on_pushButton_3_clicked();    //更新余额
    int money = ui->label_4->text().toInt();
    if(ui->startinput->text() == "开启直播"){
        QMessageBox::warning(this,"失败","当前无人开启直播,无法送礼");
        return;
    }
    if(money < 500){
        QMessageBox::warning(this,"余额","余额不足");
        return ;
    }
    Protocol p;
    p.setType(Protocol::gift);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["money"] = 500;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_flower_clicked()  //飞机
{
    this->on_pushButton_3_clicked();    //更新余额
    int money = ui->label_4->text().toInt();
    if(ui->startinput->text() == "开启直播"){
        QMessageBox::warning(this,"失败","当前无人开启直播,无法送礼");
        return;
    }
    if(money < 100){
        QMessageBox::warning(this,"余额","余额不足");
        return ;
    }
    Protocol p;
    p.setType(Protocol::gift);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["money"] = 100;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_good_clicked()    //送轮船
{
    this->on_pushButton_3_clicked();    //更新余额
    int money = ui->label_4->text().toInt();
    if(ui->startinput->text() == "开启直播"){
        QMessageBox::warning(this,"失败","当前无人开启直播,无法送礼");
        return;
    }
    if(money < 50){
        QMessageBox::warning(this,"余额","余额不足");
        return ;
    }
    Protocol p;
    p.setType(Protocol::gift);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["money"] = 50;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::on_FbBtn_clicked()   //送鱼翅
{
    this->on_pushButton_3_clicked();    //更新余额
    int money = ui->label_4->text().toInt();
    if(ui->startinput->text() == "开启直播"){
        QMessageBox::warning(this,"失败","当前无人开启直播,无法送礼");
        return;
    }
    if(money < 10){
        QMessageBox::warning(this,"余额","余额不足");
        return ;
    }
    Protocol p;
    p.setType(Protocol::gift);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["money"] = 10;
    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void ChatRoom::onrocket()
{
    Protocol p;
    p.setType(Protocol::chat);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["chat"] = "送了一个火箭";
    ClientSocketManager::getInstance()->write(p.toByteArray());

    cameraW->onrocket();
}

void ChatRoom::onplane()
{
    Protocol p;
    p.setType(Protocol::chat);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["chat"] = "送了一个飞机";
    ClientSocketManager::getInstance()->write(p.toByteArray());

    cameraW->onplane();
}

void ChatRoom::onlunchuan()
{
    Protocol p;
    p.setType(Protocol::chat);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["chat"] = "送了一个轮船";
    ClientSocketManager::getInstance()->write(p.toByteArray());

    cameraW->ongift(1);
}

void ChatRoom::onyuchi()
{
    Protocol p;
    p.setType(Protocol::chat);
    p["username"] = username;
    p["roomname"] = roomname_;
    p["chat"] = "送了一个鱼翅";
    ClientSocketManager::getInstance()->write(p.toByteArray());

    cameraW->ongift(2);
}
