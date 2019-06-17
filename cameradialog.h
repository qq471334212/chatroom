#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QHBoxLayout>
namespace Ui {
class cameraDialog;
}

class cameraDialog : public QWidget
{
    Q_OBJECT

public:
    explicit cameraDialog(QWidget *parent = nullptr);
    ~cameraDialog();

private:
    Ui::cameraDialog *ui;
    QCamera* camera;    //摄像头的类
    QCameraViewfinder* cvf;
    QCameraImageCapture* cic;
    QLabel *displayLabel;
    QHBoxLayout *mainlayout_1;
    void Init();
};

#endif // CAMERADIALOG_H
