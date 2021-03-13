#include "tweenedanimation.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QDebug>

TweenedAnimation::TweenedAnimation(QWidget *parent) : QWidget(parent),
    m_opacity(1),
    m_animationTargetLabel(nullptr),
    m_propertyAnimation(nullptr),
    m_tweenedTargetWidget(nullptr)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);

    initUI();
}

TweenedAnimation::~TweenedAnimation()
{

}

void TweenedAnimation::setTweenedAnimationWidget(QWidget* widget)
{
    if(widget != nullptr)
    {
        m_tweenedTargetWidget = widget;

        resize(m_tweenedTargetWidget->size());

        updateAnimationWidgetPixmap();
    }
}

void TweenedAnimation::start()
{
    if(m_propertyAnimation != nullptr)
    {
        updateAnimationWidgetPixmap();

        m_propertyAnimation->start();

        if(m_tweenedTargetWidget != nullptr)
        {
            m_tweenedTargetWidget->hide();
        }
    }
}

void TweenedAnimation::stop()
{
    if(m_propertyAnimation != nullptr)
    {
        m_propertyAnimation->stop();
    }
}

void TweenedAnimation::setDuration(int msecs)
{
    if(m_propertyAnimation != nullptr)
    {
        m_propertyAnimation->setDuration(msecs);
    }
}

int TweenedAnimation::duration() const
{
    int ret = -1;

    if(m_propertyAnimation != nullptr)
    {
        ret = m_propertyAnimation->duration();
    }

    return ret;
}

void TweenedAnimation::setDirection(Direction direction)
{
    if(m_propertyAnimation != nullptr && direction != Invalid)
    {
        m_propertyAnimation->setDirection((direction == Forward) ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    }
}

TweenedAnimation::Direction TweenedAnimation::direction() const
{
    TweenedAnimation::Direction ret = Invalid;

    if(m_propertyAnimation != nullptr)
    {
        ret = (m_propertyAnimation->direction() == QAbstractAnimation::Forward) ? Forward : Backward;
    }

    return ret;
}

QVariant TweenedAnimation::startValue() const
{
    QVariant ret;

    if(m_propertyAnimation != nullptr)
    {
        ret = m_propertyAnimation->startValue();
    }

    return ret;
}

void TweenedAnimation::setStartValue(const QVariant& value)
{
    if(m_propertyAnimation != nullptr)
    {
        m_propertyAnimation->setStartValue(value);
    }
}

QVariant TweenedAnimation::endValue() const
{
    QVariant ret;

    if(m_propertyAnimation != nullptr)
    {
        ret = m_propertyAnimation->endValue();
    }

    return ret;
}

void TweenedAnimation::setEndValue(const QVariant& value)
{
    if(m_propertyAnimation != nullptr)
    {
        m_propertyAnimation->setEndValue(value);
    }
}

void TweenedAnimation::setLoopCount(int loopCount)
{
    if(m_propertyAnimation != nullptr)
    {
        m_propertyAnimation->setLoopCount(loopCount);
    }
}

int TweenedAnimation::loopCount() const
{
    int ret = -1;

    if(m_propertyAnimation != nullptr)
    {
        ret = m_propertyAnimation->loopCount();
    }

    return ret;
}

bool TweenedAnimation::setWidgetOpacity(qreal opacity)
{
    bool ret = (m_tweenedTargetWidget != nullptr) && (m_animationTargetLabel != nullptr)
            && (0 <= opacity) && (opacity <= 1) && !m_animationWidgetPixmap.isNull();

    if(ret)
    {
        if(!qFuzzyCompare(m_opacity, opacity))
        {
            QPixmap pixmap(m_animationWidgetPixmap.size());
            pixmap.fill(Qt::transparent);
            pixmap.setDevicePixelRatio(m_animationWidgetPixmap.devicePixelRatio());

            QPainter painter(&pixmap);
            painter.setOpacity(opacity);
            painter.drawPixmap(QRect(0, 0, m_tweenedTargetWidget->width(), m_tweenedTargetWidget->height()), m_animationWidgetPixmap);

            m_animationTargetLabel->setPixmap(pixmap);

            m_opacity = opacity;
        }
    }

    return ret;
}

qreal TweenedAnimation::widgetOpacity()
{
    return m_opacity;
}

void TweenedAnimation::initUI()
{
    m_propertyAnimation = new QPropertyAnimation(this, "widgetOpacity", this);
    m_propertyAnimation->setDuration(1000);
    m_propertyAnimation->setStartValue(1);
    m_propertyAnimation->setEndValue(0);
    connect(m_propertyAnimation, &QPropertyAnimation::finished, this, &TweenedAnimation::finished);
    connect(m_propertyAnimation, &QPropertyAnimation::stateChanged, this, &TweenedAnimation::stateChanged);
    connect(m_propertyAnimation, &QPropertyAnimation::currentLoopChanged, this, &TweenedAnimation::currentLoopChanged);
    connect(m_propertyAnimation, &QPropertyAnimation::directionChanged, this, &TweenedAnimation::directionChanged);
    connect(m_propertyAnimation, &QPropertyAnimation::valueChanged, this, &TweenedAnimation::valueChanged);

    m_animationTargetLabel = new QLabel(this);
    m_animationTargetLabel->setScaledContents(true);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_animationTargetLabel);

    setLayout(mainLayout);
}

void TweenedAnimation::updateAnimationWidgetPixmap()
{
    if(m_tweenedTargetWidget != nullptr)
    {
        m_animationWidgetPixmap = m_tweenedTargetWidget->grab();
    }
}

