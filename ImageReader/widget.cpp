#include "widget.h"
#include <QImageReader>
#include <QLabel>
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel(this);
    label->setFixedSize(200, 900);

    QImageReader reader("D:/timg.jpg");
    reader.setClipRect(QRect(600, 0, 200, 900));
    reader.setClipRect(QRect(0, 0, 200, 900));

    QPixmap pixmap = QPixmap::fromImageReader(&reader);
    label->setPixmap(pixmap);
}

Widget::~Widget()
{

}

