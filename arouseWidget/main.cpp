#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget widget;
    widget.resize(200, 200);
    widget.show();

    return a.exec();
}
