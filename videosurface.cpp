#include "videosurface.h"

VideoSurface::VideoSurface(QObject* parent)
    :QAbstractVideoSurface (parent)
{

}
QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    //返回图像的处理格式
    Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>()<<QVideoFrame::Format_RGB32;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    emit videochanged(frame);
    return true;
}
