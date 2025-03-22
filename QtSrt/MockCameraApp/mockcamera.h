#ifndef MOCKCAMERA_H
#define MOCKCAMERA_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include <QVideoFrame>
#include <QVideoSink>
#include <QSize>

class MockCamera : public QObject
{
    Q_OBJECT
        Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
        Q_PROPERTY(QSize resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
        Q_PROPERTY(int frameRate READ frameRate WRITE setFrameRate NOTIFY frameRateChanged)

public:
    explicit MockCamera(QObject* parent = nullptr);
    ~MockCamera();

    bool isActive() const;
    void setActive(bool active);

    QSize resolution() const;
    void setResolution(const QSize& resolution);

    int frameRate() const;
    void setFrameRate(int frameRate);

    void setVideoSink(QVideoSink* sink);

signals:
    void activeChanged();
    void resolutionChanged();
    void frameRateChanged();

private slots:
    void generateFrame();

private:
    QImage generateTestPattern();
    void updateTimer();

    bool m_active;
    QTimer m_frameTimer;
    QSize m_resolution;
    int m_frameRate;
    QVideoSink* m_videoSink;
    int m_frameCount;
};

#endif // MOCKCAMERA_H
