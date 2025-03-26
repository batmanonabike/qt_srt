#include <QUrl>
#include <QPainter>
#include <QDateTime>
#include <QMediaFormat>
#include <QRandomGenerator>
#include <QtSrtMainLib/MockCamera.h>

MockCamera::MockCamera(QObject* parent)
    : QObject(parent)
    , m_active(false)
    , m_resolution(640, 480)
    , m_frameRate(30)
    , m_videoSink(nullptr)
    , m_frameCount(0)
    , m_camera(this)
    , m_mediaRecorder(this)
{
    connect(&m_frameTimer, &QTimer::timeout, this, &MockCamera::generateFrame);

    // Set up the camera and media recorder
    m_captureSession.setCamera(&m_camera);
    m_captureSession.setRecorder(&m_mediaRecorder);

    // Configure the media recorder
    m_mediaRecorder.setMediaFormat(QMediaFormat::MPEG4);
    //m_mediaRecorder.setMediaFormat(QMediaFormat::FileFormat::);
    m_mediaRecorder.setQuality(QMediaRecorder::HighQuality);
    m_mediaRecorder.setOutputLocation(QUrl::fromLocalFile("output.ts"));
}

MockCamera::~MockCamera()
{
    setActive(false);
}

bool MockCamera::isActive() const
{
    return m_active;
}

void MockCamera::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active = active;
    updateTimer();
    emit activeChanged();

    if (m_active) {
        m_camera.start();
        m_mediaRecorder.record();
    }
    else {
        m_mediaRecorder.stop();
        m_camera.stop();
    }
}

QSize MockCamera::resolution() const
{
    return m_resolution;
}

void MockCamera::setResolution(const QSize& resolution)
{
    if (m_resolution == resolution)
        return;

    m_resolution = resolution;
    emit resolutionChanged();
}

int MockCamera::frameRate() const
{
    return m_frameRate;
}

void MockCamera::setFrameRate(int frameRate)
{
    if (m_frameRate == frameRate)
        return;

    m_frameRate = frameRate;
    updateTimer();
    emit frameRateChanged();
}

void MockCamera::setVideoSink(QVideoSink* sink)
{
    m_videoSink = sink;
}

void MockCamera::updateTimer()
{
    if (m_active && m_frameRate > 0) {
        int interval = 1000 / m_frameRate;
        m_frameTimer.start(interval);
    }
    else {
        m_frameTimer.stop();
    }
}

void MockCamera::generateFrame()
{
    if (!m_videoSink)
        return;

    QImage image = generateTestPattern();

    // Create a video frame from the QImage
    QVideoFrame frame(QVideoFrameFormat(image.size(), QVideoFrameFormat::Format_BGRA8888));
    if (frame.map(QVideoFrame::WriteOnly)) {
        // Copy the image data to the video frame
        memcpy(frame.bits(0), image.constBits(), image.sizeInBytes());
        frame.unmap();
        m_videoSink->setVideoFrame(frame);
    }

    m_frameCount++;
}

QImage MockCamera::generateTestPattern()
{
    QImage image(m_resolution, QImage::Format_ARGB32);
    QPainter painter(&image);

    // Fill background
    painter.fillRect(image.rect(), Qt::black);

    // Draw color bars
    int barWidth = image.width() / 8;
    const QColor colors[] = {
        Qt::white, Qt::yellow, Qt::cyan, Qt::green,
        Qt::magenta, Qt::red, Qt::blue, Qt::black
    };

    for (int i = 0; i < 8; ++i) {
        painter.fillRect(i * barWidth, 0, barWidth, image.height() * 0.7, colors[i]);
    }

    // Add a moving element to simulate camera motion
    int circleSize = qMin(image.width(), image.height()) / 8;
    int x = (m_frameCount * 5) % (image.width() - circleSize);
    int y = image.height() * 0.8;

    painter.setBrush(Qt::red);
    painter.drawEllipse(x, y, circleSize, circleSize);

    // Add timestamp
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    painter.drawText(10, 30, "Mock Android Camera");
    painter.drawText(10, 60, timestamp);
    painter.drawText(10, 90, QString("Frame: %1").arg(m_frameCount));

    // Add some random noise to simulate camera grain
    if (m_frameCount % 10 == 0) {
        for (int i = 0; i < 100; ++i) {
            int nx = QRandomGenerator::global()->bounded(image.width());
            int ny = QRandomGenerator::global()->bounded(image.height());
            image.setPixelColor(nx, ny, Qt::white);
        }
    }

    return image;
}
