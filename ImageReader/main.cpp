#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QMovie>
#include <QBitmap>
#include <QPainter>
#include "roundedapnganimationlabel.h"
#include <QWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.resize(292, 254);
    QVBoxLayout layout;

    QMovie movie("D:/work/axxstudent/Bin/Environment/images/groupRoom/openCurtainAnimation.png", "apng");

//    movie.setScaledSize(QSize(100, 100));

    QLabel label;
    label.resize(292, 254);
    label.setScaledContents(true);
    QBitmap mask(label.size());
    QPainter painterMask(&mask);
    painterMask.setRenderHint(QPainter::Antialiasing);
    painterMask.setRenderHint(QPainter::SmoothPixmapTransform);
    painterMask.fillRect(0, 0, label.size().width(), label.size().height(), Qt::white);
    painterMask.setBrush(QColor(0, 0, 0));
    painterMask.drawRoundedRect(0, 0, label.size().width(), label.size().height(), 20, 20);
    label.setMask(mask);

    label.setMovie(&movie);
    layout.addWidget(&label);
    w.setLayout(&layout);

    w.show();
    movie.start();
//    RoundedApnganimationLabel animation;
//    animation.setApnganimationFileName("D:/work/axxstudent/Bin/Environment/images/groupRoom/openCurtainAnimation.png");
//    animation.setApngRoundedRadius(20);
//    layout.addWidget(&animation);
//    w.setLayout(&layout);
//    w.show();
//    animation.startApnganimation();

    return a.exec();
}
