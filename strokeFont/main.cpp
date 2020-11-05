#include <QApplication>
#include <QDebug>
#include "strokefont.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StrokeFont w;

    w.setRotate(-13);
    w.setText(QStringLiteral("啊撒打@#——算打good123奥术大师"));
    w.setStrokeFont(QColor("#000000"), QColor("#FFFFFF"), 8, 30);   //FFA600    000000

    qDebug() << "size = " << w.size();

    w.show();

    return a.exec();
}
