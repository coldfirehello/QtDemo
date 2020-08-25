#include "radialgradient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RadialGradient w;
    w.show();
    return a.exec();
}
