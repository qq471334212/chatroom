#include "camerawidget.h"
#include "ui_camerawidget.h"
#include <QPushButton>
#include <QCameraInfo>
#include "videosurface.h"
#include "clientsocketmanager.h"
#include <QBuffer>
#include <QAnimationDriver>
cameraWidget::cameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cameraWidget)
{
    label = new QLabel(this);
    label_2 = new QLabel(this);
    btn_1 = new QPushButton(this);
    timer_1 = new QTimer(this);
    timer_2 = new QTimer(this);
    username = "";
    roomname = "";
    ui->setupUi(this);
    Init();
    QObject::connect(timer_1,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    QObject::connect(timer_2,SIGNAL(timeout()),SLOT(onTimerOut_1()));
}
void cameraWidget::Init()               //
{
    QCameraInfo info = QCameraInfo::defaultCamera();
    camera = new QCamera(info,this);
    VideoSurface *vf = new VideoSurface(this);
    camera->setViewfinder(vf);
    QObject::connect(vf,SIGNAL(videochanged(QVideoFrame)),
                            SLOT(onvideoChanged(QVideoFrame)));        //监听摄像头每一帧的图片


    //建立udp网络连接
    socketWrite = new QUdpSocket(this);
    socketRead = new QUdpSocket(this);
    groupAddress.setAddress ("224.0.1.200");
    // groupAddress.setAddress ("239.88.88.88");   //组播地址
    socketWrite->setSocketOption (QAbstractSocket::MulticastTtlOption,1);//设置套接字属性
    socketRead->bind (QHostAddress::AnyIPv4, 8888,
                            QUdpSocket::ReuseAddressHint|QUdpSocket::ShareAddress);//绑定广播地址端口
    socketRead->joinMulticastGroup (groupAddress);  //添加到组播，绑定到读套接字上

    QObject::connect (socketRead, SIGNAL(readyRead()),
             this, SLOT(UdpReadRead()));
}
cameraWidget::~cameraWidget()
{
    delete ui;
    delete camera;
}

void cameraWidget::startResponded()
{
    camera->start();
}

void cameraWidget::stopResponded()
{
    camera->stop();
}



void cameraWidget::onvideoChanged(QVideoFrame curFrame)
{
    static int i = 0;
    i++;
    QVideoFrame frame(curFrame);
    frame.map(QAbstractVideoBuffer::ReadWrite);
    //通过QVideoFrame对象构建QImage对象
    QImage image(frame.bits(),
                  frame.width(),
                 frame.height(),
                 QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));

    //将图像旋转180
    QMatrix matrix;
    matrix.rotate(180);
    image = image.transformed(matrix);
    image = image.scaled (160,96); //将图片的大小确定
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer,"JPG");

    if(i % 4 != 0){
        int sizeInBytes = image.sizeInBytes();
        int readed = 0;
        uchar* data = image.bits();
        while(readed < sizeInBytes){
            qint64 count = socketWrite->writeDatagram((char*)data + readed,
                    1024, QHostAddress::Broadcast,8888);
            readed += count;
        }
    }
}
void cameraWidget::UdpReadRead()
{
    static QByteArray byteArray(500000,0);   //字符数组；
        //数据流
    static QDataStream dataStream(&byteArray,QIODevice::ReadWrite);
    static int readed = 0;
    while(socketRead->hasPendingDatagrams()){           //至少有一个数据在读写,否则返回false
        char buffer[1024] = {0};
        readed += socketRead->readDatagram(buffer,1024);
        dataStream.writeRawData(buffer,1024);
    }

    if(readed>=102400){
        QImage image = QImage((uchar*)byteArray.data(),
                       160,
                       96,
                       640,
                       QImage::Format_RGB32);
        QPixmap map =QPixmap::fromImage(image);
        map = map.scaled (ui->video->size ());
        ui->video->setPixmap(map);
        readed = 0;
        dataStream.device ()->seek (0);
    }
}

void cameraWidget::closeEvent(QCloseEvent *event)
{
    if(ClientSocketManager::getInstance()->isValid()){
        event->ignore();
    }else{
        event->accept();
        return;
    }

    Protocol p;
    p.setType(Protocol::quitLive);
    p["username"] = username;
    p["roomname"] = roomname;

    ClientSocketManager::getInstance()->write(p.toByteArray());
}

void cameraWidget::onsigBs (QString data)
{
    QString bs_text = data;
    label->clear();
    delete label;
    label = new QLabel(bs_text,ui->video);
    label->setStyleSheet("color:blue");             //设置弹幕颜色
    label->setFont(QFont("宋体", 25 , QFont::Bold));      //设置弹幕字体
    int len = qrand()% ui->danmu->height() + 1;     //纵坐标为随机值
    label->move(0, len);        //设置标签初始值
    label->adjustSize(); //设置label大小自适应字体长度
    timer_1->start(10);         //触发计时器
}

void cameraWidget::onTimeOut()
{
    const QPoint& p = label->pos();
    if(p.x() < (ui->danmu->width())){   //弹幕当前的x轴  和弹幕的宽度比较
        label->move(p.x() + 1, p.y());
        label->show();
        //label->update();
    }else{
        label->hide();
        timer_1->stop();
    }
}

//功能:礼物部分
void cameraWidget::onTimerOut_1(){
    const QPoint& p = btn_1->pos();
    if(p.y() > -70){
        btn_1->move(p.x(),p.y()-1);
        btn_1->show();
    }else{
        btn_1->hide();
        timer_2->stop();
    }
}

void cameraWidget::onrocket()
{
    QPixmap rocket(":/new/prefix1/image/rocket.png");
    btn_1->setText("");
    delete btn_1;
    btn_1 = new QPushButton(ui->video);

    btn_1->setIcon(rocket);
    btn_1->setIconSize(QSize(50,80));
    btn_1->move(100,300);
    timer_2->start(10);
}

void cameraWidget::onplane()
{
    QPixmap rocket(":/new/prefix1/image/plane.png");
    btn_1->setText("");
    delete btn_1;
    btn_1 = new QPushButton(ui->video);

    btn_1->setIcon(rocket);
    btn_1->setIconSize(QSize(50,80));
    btn_1->move(100,300);
    timer_2->start(10);
}

void cameraWidget::ongift(int)
{

}
QString cameraWidget::getUsername() const
{
    return username;
}
void cameraWidget::setUsername(const QString &value)
{
    username = value;
}
QString cameraWidget::getRoomname() const
{
    return roomname;
}
void cameraWidget::setRoomname(const QString &value)
{
    roomname = value;
}
