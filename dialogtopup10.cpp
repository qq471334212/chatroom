#include "dialogtopup10.h"
#include "ui_dialogtopup10.h"

Dialogtopup10::Dialogtopup10(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogtopup10)
{
    ui->setupUi(this);
}

Dialogtopup10::~Dialogtopup10()
{
    delete ui;
}
