#include "CameraFeed.h"
#include <QVBoxLayout>

CameraFeed::CameraFeed(QWidget* parent) : QWidget(parent)
{
    camera = new QCamera(this);
    captureSession = new QMediaCaptureSession(this);
    videoWidget = new QVideoWidget(this);

    captureSession->setCamera(camera);
    captureSession->setVideoOutput(videoWidget);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    setLayout(layout);

    camera->start();
}

CameraFeed::~CameraFeed()
{
    camera->stop();
}

