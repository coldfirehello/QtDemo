#include <QApplication>
#include "strokefont.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StrokeFont w;
    w.setText(QStringLiteral("麦克风不可用，快去查查吧"));
    w.setStrokeFont(QColor("#FFA600"), QColor("#FFFFFF"), 2, 20);
    w.show();

    return a.exec();
}
