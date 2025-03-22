#include "VideoPlayer.h"
#include <QDebug>

VideoPlayer::VideoPlayer(QQuickItem *parent)
    : QQuickItem(parent), pipeline(nullptr) {
    gst_init(nullptr, nullptr);
}

VideoPlayer::~VideoPlayer() {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
}

QString VideoPlayer::source() const {
    return m_source;
}

void VideoPlayer::setSource(const QString &source) {
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged();

    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

    pipeline = gst_parse_launch(
        QString("playbin uri=%1").arg(m_source).toUtf8().constData(), nullptr);

    if (!pipeline) {
        qWarning() << "Failed to create GStreamer pipeline";
        return;
    }

    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

void VideoPlayer::releaseResources() {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }
}
