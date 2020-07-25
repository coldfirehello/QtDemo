#include "volume.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Volume w;
    w.show();
    return a.exec();
}
