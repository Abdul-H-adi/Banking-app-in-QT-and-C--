#include "mainqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainQt w;
    w.show();

    return a.exec();
}
