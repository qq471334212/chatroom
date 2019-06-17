#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QCloseEvent>
#include <QCoreApplication>
namespace Ui {
class cameraWidget;
}

class cameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit cameraWidget(QWidget *parent = nullptr);
    ~cameraWidget();
    void startResponded();
    void stopResponded();
    QString getRoomname() const;
    void setRoomname(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);
    void onsigBs (QString);

    void onrocket();
    void onplane();
    void ongift(int);
private slots:
//    void captureBtnResponded();
//    void saveBtnResponded();
//    void exitBtnResponded();
//    void cameraImageCaptured(int id,QImage image);
    void onvideoChanged(QVideoFrame);
    void UdpReadRead();
    void onTimeOut();
    void onTimerOut_1();

protected:
    virtual void closeEvent(QCloseEvent* ev);
private:
    Ui::cameraWidget *ui;
    QCamera* camera;    //摄像头的类
//    QCameraViewfinder* cvf;
//    QCameraImageCapture* cic;
//    QLabel *displayLabel;
//    QHBoxLayout *mainlayout_1;

    QUdpSocket *socketWrite;
    QUdpSocket *socketRead;
    QUdpSocket *socketWdaudio;
    QUdpSocket *socketRdaudio;



    QTimer *timer;
    QLabel* label;
    QLabel* label_2;
    QHostAddress groupAddress;
    QHostAddress groupAddress_1;

    QString roomname;
    QString username;
    QTimer* timer_1;
    QTimer* timer_2;
    QPushButton* btn_1;
    void Init();
};

#endif // CAMERAWIDGET_H
