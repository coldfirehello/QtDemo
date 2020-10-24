#include "hdIcon.h"

#include <QApplication>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QGridLayout>
#include "hdIcon.h"

QPixmap pixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull())
    {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);
    QPixmap image = src.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    image.setMask(mask);
    return image;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filePath = ":/images/test.jpg";

    QWidget widget;

    QGridLayout* layout = new QGridLayout();

    QLabel styleSheetLabel;
    styleSheetLabel.setFixedSize(40, 40);
    styleSheetLabel.setStyleSheet(QString("QLabel{border-radius:20px;border-image:url(%1);}").arg(filePath));

    QLabel pixmapLabel;
    pixmapLabel.setFixedSize(40, 40);
    QPixmap pixmap(filePath);
    pixmapLabel.setPixmap(pixmapToRound(pixmap, 20));

    HDIcon hdIcon;
    hdIcon.setIconInfo(filePath, QSize(40, 40), 20);

    layout->addWidget(&styleSheetLabel, 0, 0);
    layout->addWidget(&pixmapLabel, 0, 1);
    layout->addWidget(&hdIcon, 1, 0);

    widget.setLayout(layout);
    widget.show();

    return a.exec();
}
