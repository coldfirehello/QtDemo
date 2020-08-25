#include "radialgradient.h"
#include <QGridLayout>

RadialGradient::RadialGradient(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 1000);

    QGridLayout* layout = new QGridLayout();

    QWidget* w1 = new QWidget(this);
    w1->setStyleSheet("QWidget{background-color:qradialgradient(cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0 yellow, stop:0.99 yellow, stop:1 white)}");

    QWidget* w2 = new QWidget(this);
    w2->setStyleSheet("QWidget{background-color:qradialgradient(cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0 red, stop:0.99 yellow, stop:1 white)}");

    QWidget* w3 = new QWidget(this);
    w3->setStyleSheet("QWidget{background-color:qradialgradient(cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0 red, stop:0.5 blue, stop:0.99 yellow, stop:1 white)}");

    QWidget* w4 = new QWidget(this);
    w4->setStyleSheet("QWidget{background-color:qradialgradient(cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0 black, stop:0.99 yellow, stop:1 transparent)}");

    layout->addWidget(w1, 0, 0);
    layout->addWidget(w2, 0, 1);
    layout->addWidget(w3, 1, 0);
    layout->addWidget(w4, 1, 1);

    setLayout(layout);
}

RadialGradient::~RadialGradient()
{

}

