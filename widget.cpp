#include "widget.h"
#include "ui_widget.h"
#include "protocol.h"
#include "clientsocketmanager.h"
#include <QResizeEvent>
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label_3->setScaledContents(true);
    QMovie* movie = new QMovie(":/new/prefix1/image/123.gif");
    ui->label_3->setMovie(movie);
    movie->start();

    QImage _image;
    _image.load(":/new/prefix1/image/timg.jpg");
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(),
                            Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation)));
    setPalette(pal);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_loginbtn_clicked()
{

    QString username = ui->leusername->text();
    QString userpwd = ui->leuserpwd->text();

    if (!ui->cbpwd->isCheckable())
    {
        ui->leusername->clear();
        ui->leuserpwd->clear();
    }
    Protocol p;
    p.setType(Protocol::login);
    p["username"] = username;
    p["userpwd"] = userpwd;

    ClientSocketManager::getInstance()->write(p.toByteArray());

    //数据的发送信息
}

void Widget::on_registbtn_clicked()
{
    emit RegistBtn();
}

void Widget::on_leusername_returnPressed()
{
    QString username = ui->leusername->text();
    QString userpwd = ui->leuserpwd->text();

    if (!ui->cbpwd->isCheckable())
    {
        ui->leusername->clear();
        ui->leuserpwd->clear();
    }

    Protocol p;
    p.setType(Protocol::login);
    p["username"] = username;
    p["userpwd"] = userpwd;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void Widget::on_leuserpwd_returnPressed()
{
    QString username = ui->leusername->text();
    QString userpwd = ui->leuserpwd->text();

    if (!ui->cbpwd->isCheckable())
    {
        ui->leusername->clear();
        ui->leuserpwd->clear();
    }

    Protocol p;
    p.setType(Protocol::login);
    p["username"] = username;
    p["userpwd"] = userpwd;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}
