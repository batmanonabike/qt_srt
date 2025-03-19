#include <QApplication>
#include "CameraFeed.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CameraFeed cameraFeed;
    cameraFeed.show();

    return app.exec();
}
