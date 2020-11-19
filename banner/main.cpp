#include "banner.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget* widget = new QWidget();

    Banner* banner = new Banner();

    for(int i = 1; i < 8; ++i)
    {
        QString image = QString(":/%1.jpg").arg(i);
        banner->addImage(image);
    }

    QPushButton* leftBtn = new QPushButton();
    leftBtn->setText("L");

    //QPushButton* jumpBtn = new QPushButton(banner);
    //jumpBtn->setText("Jump");

    QPushButton* rightBtn = new QPushButton();
    rightBtn->setText("R");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(leftBtn);
    hLayout->addWidget(rightBtn);
    hLayout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(banner);
    layout->addLayout(hLayout);

    widget->setLayout(layout);

    Banner::connect(leftBtn, SIGNAL(clicked()), banner, SLOT(prev()));
    Banner::connect(rightBtn, SIGNAL(clicked()), banner, SLOT(next()));

    widget->show();

    return a.exec();
}
