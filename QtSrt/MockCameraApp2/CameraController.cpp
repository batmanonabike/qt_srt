#include "CameraController.h"

CameraController::CameraController(QObject* parent)
    : QObject(parent)
    , m_videoSink(nullptr)
{
}

CameraController::~CameraController()
{
}

bool CameraController::isActive() const
{
    return m_mockCamera.isActive();
}

void CameraController::setActive(bool active)
{
    if (m_mockCamera.isActive() != active) {
        m_mockCamera.setActive(active);
        emit activeChanged();
    }
}

QSize CameraController::resolution() const
{
    return m_mockCamera.resolution();
}

void CameraController::setResolution(const QSize& resolution)
{
    if (m_mockCamera.resolution() != resolution) {
        m_mockCamera.setResolution(resolution);
        emit resolutionChanged();
    }
}

int CameraController::frameRate() const
{
    return m_mockCamera.frameRate();
}

void CameraController::setFrameRate(int frameRate)
{
    if (m_mockCamera.frameRate() != frameRate) {
        m_mockCamera.setFrameRate(frameRate);
        emit frameRateChanged();
    }
}

QVideoSink* CameraController::videoSink() const
{
    return m_videoSink;
}

void CameraController::setVideoSink(QVideoSink* sink)
{
    if (m_videoSink != sink) {
        m_videoSink = sink;
        m_mockCamera.setVideoSink(sink);
        emit videoSinkChanged();
    }
}
