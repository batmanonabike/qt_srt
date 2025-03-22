#include "VideoPlayer.h"
#include <QDebug>
#include <QProcess>

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

void VideoPlayer::setSource(const QString& source) {
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged();

    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

    if (!isRtmpPluginAvailable()) {
        qWarning() << "RTMP plugin is not available";
        return;
    }

    QString pipelineDescription = QString("playbin uri=%1").arg(m_source);
    qDebug() << "Creating GStreamer pipeline with description:" << pipelineDescription;

    pipeline = gst_parse_launch(pipelineDescription.toUtf8().constData(), nullptr);

    if (!pipeline) {
        qWarning() << "Failed to create GStreamer pipeline";
        return;
    }

    GstBus* bus = gst_element_get_bus(pipeline);
    gst_bus_add_watch(bus, (GstBusFunc)bus_call, this);
    gst_object_unref(bus);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

gboolean VideoPlayer::bus_call(GstBus* bus, GstMessage* msg, gpointer data) {
    GMainLoop* loop = (GMainLoop*)data;

    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR: {
        GError* err;
        gchar* debug;
        gst_message_parse_error(msg, &err, &debug);
        g_printerr("Error: %s\n", err->message);
        g_error_free(err);
        g_free(debug);
        g_main_loop_quit(loop);
        break;
    }
    default:
        break;
    }

    return TRUE;
}

void VideoPlayer::releaseResources() {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }
}

// C:\source\repos\qt_srt_29\QtSrt\vcpkg\installed\x64-windows\tools\gstreamer\gst-inspect-1.0.exe
bool VideoPlayer::isRtmpPluginAvailable() {
    QProcess process;
    process.start("gst-inspect-1.0", QStringList() << "rtmp");

    if (!process.waitForStarted()) {
        qWarning() << "Failed to start gst-inspect-1.0 process:" << process.errorString();
        return false;
    }

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    return output.contains("rtmp");
}
