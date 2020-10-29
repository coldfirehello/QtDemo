#include <QApplication>
#include "strokefont.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StrokeFont w;
    w.setText(QStringLiteral("你是aa我的123"));
    w.setStrokeFont(QColor("#FFA600"), QColor("#FFFFFF"), 10, 50);
    w.show();

    return a.exec();
}
