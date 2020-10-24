#include "hdIcon.h"
#include <QPainter>

HDIcon::HDIcon(QWidget *parent) : QLabel(parent)
{

}

HDIcon::~HDIcon()
{

}

void HDIcon::setIconInfo(const QString &filePath, const QSize &scaledSize, int radius)
{
    QPixmap pixmap = pixmapToRound(filePath, scaledSize, radius);

    if(!pixmap.isNull())
    {
        setPixmap(pixmap);
    }
}

QPixmap HDIcon::pixmapToRound(const QString &filePath, const QSize &scaledSize, int radius)
{
    QPixmap headPixmap(scaledSize);

    QPixmap pixmap(filePath);

    if(pixmap.isNull() && !scaledSize.isValid() && radius < 0)
    {
        headPixmap = QPixmap();
    }
    else
    {
        headPixmap.fill(Qt::transparent);

        QPainter painter(&headPixmap);
        QPainterPath painterPath;
        QRect rect(0, 0, scaledSize.width(), scaledSize.height());
        painterPath.addRoundedRect(rect, radius, radius);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setClipPath(painterPath);
        painter.drawPixmap(rect, pixmap.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    return headPixmap;
}

