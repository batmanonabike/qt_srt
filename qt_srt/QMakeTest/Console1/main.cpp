#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Qt is working";
    QTimer::singleShot(5000, &a, &QCoreApplication::quit);

    return a.exec();
}
