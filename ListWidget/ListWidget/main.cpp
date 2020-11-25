#include "listwidget.h"

#include <QApplication>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ListWidget w;

    for(int i = 0; i < 15; i++)
    {
        QWidget* item = new QWidget(&w);
        item->setFixedHeight(32);
        item->setStyleSheet("QWidget{background:red;}");

        QLabel* label = new QLabel(item);
        label->setPixmap(QPixmap("D:/123.png"));

        w.addWidget(item);
    }

    w.setContentsMargins(QMargins(10, 10, 10, 10));

    w.show();

    return a.exec();
}
