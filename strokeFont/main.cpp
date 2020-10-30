#include <QApplication>
#include "strokefont.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StrokeFont w;

    w.setRotate(-73);
    w.setText(QStringLiteral("啊撒打@#——算打good123奥术大师"));
    w.setStrokeFont(QColor("#FFA600"), QColor("#FFFFFF"), 8, 30);

    w.show();

    return a.exec();
}
