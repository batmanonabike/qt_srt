#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QSize>
#include <QVideoSink>
#include "mockcamera.h"

class CameraController : public QObject
{
    Q_OBJECT
        Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
        Q_PROPERTY(QSize resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
        Q_PROPERTY(int frameRate READ frameRate WRITE setFrameRate NOTIFY frameRateChanged)
        Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
    explicit CameraController(QObject* parent = nullptr);
    ~CameraController();

    bool isActive() const;
    void setActive(bool active);

    QSize resolution() const;
    void setResolution(const QSize& resolution);

    int frameRate() const;
    void setFrameRate(int frameRate);

    QVideoSink* videoSink() const;
    void setVideoSink(QVideoSink* sink);

signals:
    void activeChanged();
    void resolutionChanged();
    void frameRateChanged();
    void videoSinkChanged();

private:
    MockCamera m_mockCamera;
    QVideoSink* m_videoSink;
};

#endif // CAMERACONTROLLER_H
