#include "widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "arousewidget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void Widget::initUI()
{
    ArouseWidget* w = new ArouseWidget(this);

    QLabel* upLabel = new QLabel(w);
    upLabel->setFixedSize(100, 40);
    upLabel->setStyleSheet("QLabel{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(0, 0, 0, 0.05),stop:1 rgba(0, 0, 0, 0.3));}");

    QLabel* downLabel = new QLabel(w);
    downLabel->setFixedSize(100, 40);
    downLabel->setStyleSheet("QLabel{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(0, 0, 0, 0.3),stop:1 rgba(0, 0, 0, 0.05));}");

    resize(200, 200);

    w->setUpWidget(upLabel);
    w->setDownWidget(downLabel);
    w->setDuration(800);

    QPushButton* startBtn = new QPushButton(this);
    startBtn->setText("start");

    QPushButton* stopBtn = new QPushButton(this);
    stopBtn->setText("stop");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setMargin(0);
    hLayout->addWidget(startBtn);
    hLayout->addWidget(stopBtn);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(hLayout);
    layout->addWidget(w);

    connect(startBtn, &QPushButton::clicked, w, &ArouseWidget::showArouseWidget);
    connect(stopBtn, &QPushButton::clicked, w, &ArouseWidget::hideArouseWidget);

    setLayout(layout);
}
