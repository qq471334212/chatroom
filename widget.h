#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

//    virtual void resizeEvent(QResizeEvent *event);

signals:
    void RegistBtn();
private slots:
    void on_loginbtn_clicked();

    void on_registbtn_clicked();

    void on_leusername_returnPressed();

    void on_leuserpwd_returnPressed();

private:
    Ui::Widget *ui;


};



#endif // WIDGET_H
