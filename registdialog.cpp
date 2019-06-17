#include "registdialog.h"
#include "ui_registdialog.h"
#include "protocol.h"
#include "clientsocketmanager.h"
registDialog::registDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registDialog)
{
    ui->setupUi(this);
    this->setObjectName("dialog");
    this->setStyleSheet("background-image: url(:/new/prefix1/image/timg.jpg);");
}

registDialog::~registDialog()
{
    delete ui;
}

void registDialog::on_pushButton_clicked()
{
        QString username = ui->lename->text();
        QString userpwd = ui->lepwd->text();
        ui->lename->clear();
        ui->lepwd->clear();

        Protocol p;
        p.setType(Protocol::regist);
        p["username"] = username;
        p["userpwd"] = userpwd;

        ClientSocketManager::getInstance()->write(p.toByteArray());
}
