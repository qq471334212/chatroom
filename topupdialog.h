#ifndef TOPUPDIALOG_H
#define TOPUPDIALOG_H

#include <QDialog>
#include "dialogtopup10.h"
namespace Ui {
class TopupDialog;
}

class TopupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TopupDialog(QWidget *parent = nullptr);
    ~TopupDialog();


signals:
    void topup(int);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::TopupDialog *ui;
    Dialogtopup10* a;
};

#endif // TOPUPDIALOG_H
