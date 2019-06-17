#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

#include <QDialog>

namespace Ui {
class registDialog;
}

class registDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registDialog(QWidget *parent = nullptr);
    ~registDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registDialog *ui;
};

#endif // REGISTDIALOG_H
