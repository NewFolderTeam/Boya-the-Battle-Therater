#include "startwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString resourcePath = QDir::currentPath();
    QDir::setCurrent(resourcePath);
    Startwindow w;
    w.show();

    return a.exec();
}
