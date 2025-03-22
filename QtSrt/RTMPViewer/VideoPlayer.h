#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QQuickItem>
#include <gst/gst.h>

class VideoPlayer : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit VideoPlayer(QQuickItem *parent = nullptr);
    ~VideoPlayer();

    QString source() const;
    void setSource(const QString &source);

signals:
    void sourceChanged();

protected:
    void releaseResources() override;

private:
    GstElement *pipeline;
    QString m_source;

    static bool isRtmpPluginAvailable();
    static gboolean bus_call(GstBus* bus, GstMessage* msg, gpointer data);
};

#endif // VIDEOPLAYER_H
