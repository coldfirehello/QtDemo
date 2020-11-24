#include "heart.h"
#include <QPainter>

Heart::Heart(QWidget *parent) : QWidget(parent)
{
    resize(1000, 1000);
}

Heart::~Heart()
{

}

void Heart::paintEvent(QPaintEvent *event)
{
    double k = 5;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor my_color(237, 162, 255, 255);
    QBrush my_brush(my_color);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.translate(this->width()/2, this->height()/2);
    QPainterPath polygonPath;
    polygonPath.setFillRule(Qt::WindingFill);
    float x = 16 * k * sin(0.0)*sin(0.0)*sin(0.0);
    float y = 13 * k * cos(0.0) - 5 * k*cos(0.0) - 2 * k*cos(0.0) - cos(0.0);
    polygonPath.moveTo(x, -y);
    for (double t = 0.01; t < 100; t += 0.05)
    {
        x = 16 * k * sin(k*t)*sin(k*t)*sin(k*t);
        y = 13 * k * cos(k*t) - 5 * k * cos(2 * k * t) - 2 * k * cos(3 * k * t) - cos(4 * k * t);
        polygonPath.lineTo(x, -y);
    }

    painter.drawPath(polygonPath);
}
