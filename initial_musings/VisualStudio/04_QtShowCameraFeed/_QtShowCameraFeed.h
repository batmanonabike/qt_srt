#pragma once

#include <QtWidgets/QMainWindow>
#include "ui__QtShowCameraFeed.h"

class _QtShowCameraFeed : public QMainWindow
{
    Q_OBJECT

public:
    _QtShowCameraFeed(QWidget *parent = nullptr);
    ~_QtShowCameraFeed();

private:
    Ui::_QtShowCameraFeedClass ui;
};
