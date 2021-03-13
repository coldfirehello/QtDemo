#include "tweenedanimation.h"

#include <QApplication>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
//    qputenv("QT_SCALE_FACTOR", QString::number(2).toLatin1());

    QApplication a(argc, argv);

    QWidget widget;
    widget.resize(1000, 1000);
    widget.move(300, 100);

    QLabel label(&widget);
    label.setText("123456");
    label.setFixedSize(200, 200);
    label.setStyleSheet("QLabel{background:red}");
    label.move(100, 100);

    QLabel label1(&widget);
    label1.setText("123456");
    label1.setFixedSize(200, 200);
    label1.setStyleSheet("QLabel{background:blue}");
    label1.move(200, 200);
    label1.hide();

    TweenedAnimation w(&widget);
    w.setTweenedAnimationWidget(&label);
    w.move(400, 0);
    w.setDuration(3000);
    w.setStartValue(0);
    w.setEndValue(1);
    w.setObjectName("w");
    w.show();

    QRect startRect = QRect(200, 200, w.width(), w.height());

    QPropertyAnimation animation;
    animation.setTargetObject(&w);
    animation.setPropertyName("geometry");
    animation.setDuration(3000);
    animation.setStartValue(QRect(350, 300, 100, 100));
    animation.setEndValue(startRect);

    TweenedAnimation w1(&widget);
    w1.setTweenedAnimationWidget(&label1);
//    w1.setWidgetOpacity(0.5);
    w1.move(350, 100);
    w1.setDuration(3000);
    w1.setStartValue(0.5);
    w1.setEndValue(1);
    w1.resize(label1.size() * 0.8);
    w1.setObjectName("w1");

    widget.show();

    animation.start();
    w.start();

    w1.start();

    return a.exec();
}
