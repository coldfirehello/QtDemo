#include "scatterflowers.h"

#include <QApplication>
#include <QDebug>
#include "scatterflowersgraphics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ScatterFlowers w;

    w.resize(1800, 800);

    w.show();

    w.startScatterFlowers();


    return a.exec();
}
