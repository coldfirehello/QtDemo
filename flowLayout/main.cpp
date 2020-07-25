#include "flowlayout.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include "flowwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlowWidget widget;
    widget.show();

    return a.exec();
}
