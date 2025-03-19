#pragma once

#include <QWidget>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoWidget>

class CameraFeed : public QWidget
{
    Q_OBJECT

public:
    explicit CameraFeed(QWidget* parent = nullptr);
    ~CameraFeed();

private:
    QCamera* camera;
    QMediaCaptureSession* captureSession;
    QVideoWidget* videoWidget;
};

