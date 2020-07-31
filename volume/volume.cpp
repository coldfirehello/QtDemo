#include "volume.h"
#include <QApplication>
#include <QEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

Volume::Volume(QWidget *parent) : QWidget(parent),
    m_slider(nullptr)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    initUI();
}

Volume::~Volume()
{

}

void Volume::setValue(int value)
{
    if(m_slider != nullptr)
    {
        m_slider->setValue(value);
    }
}

void Volume::initUI()
{
    QWidget* backgroundWidget = new QWidget(this);
    backgroundWidget->resize(36, 153);
    backgroundWidget->setStyleSheet("QWidget{background-color:rgba(0, 0, 0, 0.8);border-radius:18px;}");

    m_slider = new QSlider();
    m_slider->resize(36, 121);
    m_slider->setMaximum(100);
    m_slider->setMinimum(0);
    m_slider->setValue(0);
    m_slider->setStyleSheet("QSlider{background:transparent;}"
                            "QSlider::add-page:vertical{background-color:#FFFFFF;width:4px;border-radius:2px;}"
                            "QSlider::sub-page:vertical{background-color:rgba(196, 196, 196, 0.5);width:4px;border-radius:2px;}"
                            "QSlider::groove:vertical{background:transparent;width:4px;border-radius:2px;}"
                            "QSlider::handle:vertical{height:20px;width:20px;border-image:url(:/images/handle.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                            "QSlider::handle:vertical:hover{height:20px;width:20px;border-image:url(:/images/plus.png);margin-top:-2px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                            "QSlider::handle:vertical:pressed{height:20px;width:20px;border-image:url(:/images/plus.png);margin-top:-2px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}");
    connect(m_slider, &QSlider::valueChanged, this, &Volume::onVolumeChanged);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 16, 0, 16);
    vLayout->setAlignment(Qt::AlignCenter);
    vLayout->setSpacing(0);
    vLayout->addWidget(m_slider);

    backgroundWidget->setLayout(vLayout);

    setValue(10);
}

void Volume::onVolumeChanged()
{
    if(m_slider != nullptr)
    {
        int value = m_slider->value();

        if (value == 0)
        {
            m_slider->setStyleSheet("QSlider{background:transparent;}"
                                    "QSlider::add-page:vertical{background-color:rgba(0, 0, 0, 0.8);width:4px;border-radius:2px;}"
                                    "QSlider::sub-page:vertical{background-color:rgba(196, 196, 196, 0.5);width:4px;border-radius:2px;}"
                                    "QSlider::groove:vertical{background:transparent;width:4px;border-radius:2px;}"
                                    "QSlider::handle:vertical{height:20px;width:21px;border-image:url(:/images/handle.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:hover{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:pressed{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}");
        }
        else if (value > 0 && value < 100)
        {
            m_slider->setStyleSheet("QSlider{background:transparent;}"
                                    "QSlider::add-page:vertical{background-color:#FFFFFF;width:4px;border-radius:2px;}"
                                    "QSlider::sub-page:vertical{background-color:rgba(196, 196, 196, 0.5);width:4px;border-radius:2px;}"
                                    "QSlider::groove:vertical{background:transparent;width:4px;border-radius:2px;}"
                                    "QSlider::handle:vertical{height:20px;width:21px;border-image:url(:/images/handle.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:hover{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:pressed{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}");
        }
        else
        {
            m_slider->setStyleSheet("QSlider{background:transparent;}"
                                    "QSlider::add-page:vertical{background-color:#FFFFFF;width:4px;border-radius:2px;}"
                                    "QSlider::sub-page:vertical{background-color:rgba(0, 0, 0, 0.8);width:4px;border-radius:2px;}"
                                    "QSlider::groove:vertical{background:transparent;width:4px;border-radius:2px;}"
                                    "QSlider::handle:vertical{height:20px;width:21px;border-image:url(:/images/handle.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:hover{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}"
                                    "QSlider::handle:vertical:pressed{height:20px;width:21px;border-image:url(:/images/plus.png);margin-top:0px;margin-bottom:0px;margin-left:-8px;margin-right:-8px;}");
        }

        emit signalVolumeChanged(value);
    }
}

void Volume::paintEvent(QPaintEvent *event)
{
    QStyleOption option;

    option.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}

bool Volume::event(QEvent *e)
{
    if (e->type() == QEvent::ActivationChange)
    {
        if (QApplication::activeWindow() != this)
        {
            this->close();
        }
    }

    return QWidget::event(e);
}
