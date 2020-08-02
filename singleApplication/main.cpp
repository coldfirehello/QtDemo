#include "singleApplication.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    SignalApplication a(argc, argv, "singleApplication");

    a.setApplicationName("testSignalApplication");

    if(a.isRunning())
    {
        return EXIT_SUCCESS;
    }

    //开始正常运行
    QWidget w;
    w.show();

    return a.exec();
}
