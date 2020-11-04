#include "arousewidget.h"
#include <QVBoxLayout>

ArouseWidget::ArouseWidget(QWidget *parent) : QWidget(parent),
    m_downAnimation(nullptr),
    m_upAnimation(nullptr),
    m_arouseAnimationGroup(nullptr),
    m_downWidget(nullptr),
    m_upWidget(nullptr),
    m_downAnimationRegionWidget(nullptr),
    m_upAnimationRegionWidget(nullptr)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    initUI();
}

ArouseWidget::~ArouseWidget()
{

}

void ArouseWidget::setUpWidget(QWidget *widget)
{
    if(widget != nullptr && m_upAnimation != nullptr && m_upAnimationRegionWidget != nullptr && m_arouseAnimationGroup != nullptr)
    {
        if(widget != m_upWidget && m_upWidget != nullptr)
        {
            m_upWidget->setParent(nullptr);
        }

        m_upAnimationRegionWidget->setFixedHeight(widget->height());
        widget->setParent(m_upAnimationRegionWidget);
        m_upWidget = widget;
        m_upWidget->hide();

        m_upAnimation->setTargetObject(widget);
        m_arouseAnimationGroup->addAnimation(m_upAnimation);

        updateUpAnimation();
    }
}

void ArouseWidget::setDownWidget(QWidget *widget)
{
    if(widget != nullptr && m_downAnimation != nullptr && m_downAnimationRegionWidget != nullptr && m_arouseAnimationGroup != nullptr)
    {
        if(widget != m_downWidget && m_downWidget != nullptr)
        {
            m_downWidget->setParent(nullptr);
        }

        m_downAnimationRegionWidget->setFixedHeight(widget->height());
        widget->setParent(m_downAnimationRegionWidget);
        m_downWidget = widget;
        m_downWidget->hide();

        m_downAnimation->setTargetObject(widget);
        m_arouseAnimationGroup->addAnimation(m_downAnimation);

        updateDownAnimation();
    }
}

void ArouseWidget::setDuration(int msecs)
{
    if(m_downAnimation != nullptr && m_upAnimation != nullptr)
    {
        m_downAnimation->setDuration(msecs);
        m_upAnimation->setDuration(msecs);
    }
}

void ArouseWidget::hideArouseWidget()
{
    if(m_arouseAnimationGroup != nullptr && ((m_upWidget != nullptr && m_upWidget->isVisible()) || (m_downWidget != nullptr && m_downWidget->isVisible())))
    {
        m_arouseAnimationGroup->setDirection(QAbstractAnimation::Backward);
        m_arouseAnimationGroup->start();

        if(m_upWidget != nullptr)
        {
            m_upWidget->show();
        }

        if(m_downWidget != nullptr)
        {
            m_downWidget->show();
        }
    }
}

void ArouseWidget::showArouseWidget()
{
    if(m_arouseAnimationGroup != nullptr && ((m_upWidget != nullptr && m_upWidget->isHidden()) || (m_downWidget != nullptr && m_downWidget->isHidden())))
    {
        show();

        m_arouseAnimationGroup->setDirection(QAbstractAnimation::Forward);
        m_arouseAnimationGroup->start();

        if(m_upWidget != nullptr)
        {
            m_upWidget->show();
        }

        if(m_downWidget != nullptr)
        {
            m_downWidget->show();
        }
    }
}

void ArouseWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateUpAnimation();
    updateDownAnimation();
}

void ArouseWidget::initUI()
{
    m_downAnimation = new QPropertyAnimation(this);
    m_downAnimation->setDuration(3000);
    m_downAnimation->setPropertyName("geometry");
    m_downAnimation->setEasingCurve(QEasingCurve::Linear);

    m_upAnimation = new QPropertyAnimation(this);
    m_upAnimation->setDuration(3000);
    m_upAnimation->setPropertyName("geometry");
    m_upAnimation->setEasingCurve(QEasingCurve::Linear);

    m_arouseAnimationGroup = new QParallelAnimationGroup(this);
    connect(m_arouseAnimationGroup, &QParallelAnimationGroup::finished, this, [=]{
        if(m_arouseAnimationGroup->direction() == QAbstractAnimation::Backward)
        {
            if(m_upWidget != nullptr)
            {
                m_upWidget->hide();
            }

            if(m_downWidget != nullptr)
            {
                m_downWidget->hide();
            }
        }
    });

    m_downAnimationRegionWidget = new QWidget(this);

    m_upAnimationRegionWidget = new QWidget(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_downAnimationRegionWidget);
    layout->addStretch();
    layout->addWidget(m_upAnimationRegionWidget);

    setLayout(layout);
}

void ArouseWidget::updateUpAnimation()
{
    if(m_upAnimation != nullptr && m_upAnimation->targetObject() != nullptr && m_upAnimationRegionWidget != nullptr)
    {
        QWidget* widget = qobject_cast<QWidget*>(m_upAnimation->targetObject());

        if(m_arouseAnimationGroup->state() != QAbstractAnimation::Running)
        {
            QRect start(0, m_upAnimationRegionWidget->height(), widget->width(), widget->height());
            m_upAnimation->setStartValue(start);
        }
        else
        {
            widget->move(0, m_upAnimationRegionWidget->height() - widget->height());
        }

        widget->setFixedWidth(m_upAnimationRegionWidget->width());

        QRect end(0, m_upAnimationRegionWidget->height() - widget->height(), widget->width(), widget->height());
        m_upAnimation->setEndValue(end);
    }
}

void ArouseWidget::updateDownAnimation()
{
    if(m_downAnimation != nullptr && m_downAnimation->targetObject() != nullptr && m_downAnimationRegionWidget != nullptr)
    {
        QWidget* widget = qobject_cast<QWidget*>(m_downAnimation->targetObject());

        if(m_arouseAnimationGroup->state() != QAbstractAnimation::Running)
        {
            QRect start(0, -m_downAnimationRegionWidget->height(), widget->width(), widget->height());
            m_downAnimation->setStartValue(start);
        }

        widget->setFixedWidth(m_downAnimationRegionWidget->width());

        QRect end(0, 0, widget->width(), widget->height());
        m_downAnimation->setEndValue(end);
    }
}
