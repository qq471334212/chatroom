#include "topupdialog.h"
#include "ui_topupdialog.h"
TopupDialog::TopupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopupDialog),
    a(new Dialogtopup10)
{
    ui->setupUi(this);
}

TopupDialog::~TopupDialog()
{
    delete ui;
    delete a;
}


void TopupDialog::on_pushButton_clicked()   //10
{
    a->show();
    int b = 10;

    emit topup(b);
}

void TopupDialog::on_pushButton_2_clicked() //50
{
    a->show();
    int b = 50;
    emit topup(b);
}

void TopupDialog::on_pushButton_3_clicked() //100
{
    a->show();
    int b = 100;
    emit topup(b);
}

void TopupDialog::on_pushButton_4_clicked() //200
{
    a->show();
    int b = 200;
    emit topup(b);
}

void TopupDialog::on_pushButton_5_clicked() //500
{
    a->show();
    int b = 500;
    emit topup(b);
}

void TopupDialog::on_lineEdit_returnPressed()   //任意金额
{
    int b = ui->lineEdit->text().toInt();
    a->show();
    emit topup(b);
}
