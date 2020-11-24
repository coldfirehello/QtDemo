#include "banner.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>

Banner::Banner(QWidget *parent) : QWidget(parent)
{
    setCursor(Qt::PointingHandCursor);

    m_isAnimation = false;
    m_index = 0;
    m_animationType = AnimationType::UnKnow;

    m_leftAnimation = new QPropertyAnimation(this, ""); //一定要
    m_leftAnimation->setDuration(300);

    m_centerAnimation = new QPropertyAnimation(this, "");
    m_centerAnimation->setDuration(300);

    m_rightAnimation = new QPropertyAnimation(this, "");
    m_rightAnimation->setDuration(300);

    m_animationGroup = new QParallelAnimationGroup(this);
    m_animationGroup->addAnimation(m_leftAnimation);
    m_animationGroup->addAnimation(m_centerAnimation);
    m_animationGroup->addAnimation(m_rightAnimation);

    connect(m_leftAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged(QVariant)));
    connect(m_centerAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged(QVariant)));
    connect(m_rightAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged(QVariant)));
    connect(m_centerAnimation, SIGNAL(finished()), this, SLOT(finished()));

    resize(770, 200);
}

Banner::~Banner()
{

}

void Banner::addImage(const QString &image)
{
    m_imageList.append(image);
}

void Banner::next()
{
    if(!m_isAnimation)
    {
        m_animationType = Next;
        m_isAnimation = true;

        m_leftAnimation->setStartValue(QRect(115, 0, 540, 200));
        m_leftAnimation->setEndValue(QRect(0, 10, 503, 190));

        m_centerAnimation->setStartValue(QRect(267, 10, 503, 190));
        m_centerAnimation->setEndValue(QRect(115, 0, 540, 200));

        m_rightAnimation->setStartValue(QRect(152, 10, 503, 190));
        m_rightAnimation->setEndValue(QRect(267, 10, 503, 190));

        m_leftAnimation->start();
        m_centerAnimation->start();
        m_rightAnimation->start();

        update();
    }
}

void Banner::prev()
{
    if(!m_isAnimation)
    {
        m_animationType = Prev;
        m_isAnimation = true;

        m_leftAnimation->setStartValue(QRect(115, 10, 503, 190));
        m_leftAnimation->setEndValue(QRect(0, 10, 503, 190));

        m_centerAnimation->setStartValue(QRect(0, 10, 503, 190));
        m_centerAnimation->setEndValue(QRect(115, 0, 540, 200));

        m_rightAnimation->setStartValue(QRect(115, 0, 540, 200));
        m_rightAnimation->setEndValue(QRect(267, 10, 503, 190));

        m_leftAnimation->start();
        m_centerAnimation->start();
        m_rightAnimation->start();

        update();
    }
}

void Banner::jump(int index)
{
    if(!m_isAnimation)
    {
        if(index < m_imageList.size())
        {
            m_index = index;

            m_animationType = Jump;
            m_isAnimation = true;

            m_leftAnimation->setStartValue(QRect(115, 10, 503, 190));
            m_leftAnimation->setEndValue(QRect(0, 10, 503, 190));

            m_centerAnimation->setStartValue(QRect(this->rect().center().x(), this->rect().center().y(), 0, 0));
            m_centerAnimation->setEndValue(QRect(115, 0, 540, 200));

            m_rightAnimation->setStartValue(QRect(115, 10, 503, 190));
            m_rightAnimation->setEndValue(QRect(267, 10, 503, 190));

            m_leftAnimation->start();
            m_centerAnimation->start();
            m_rightAnimation->start();

            update();
        }
    }
}

void Banner::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    if(m_imageList.count() < 3)
    {
        painter.drawText(this->geometry(), Qt::AlignCenter, QString::fromLocal8Bit("3 picture"));
    }
    else
    {
        drawLeft(&painter);
        drawRight(&painter);
        drawCenter(&painter);
    }
}

void Banner::drawLeft(QPainter *painter)
{
    painter->save();

    if(!m_isAnimation)
    {
        int leftIndex = (m_index + m_imageList.size() - 1) % m_imageList.size();
        QImage leftImage = QImage(m_imageList.at(leftIndex)).scaled(503, 190);
        painter->drawImage(QRect(0, 10, 504, 190), getGrayImage(leftImage));
    }
    else
    {
        if(m_animationType == Next)
        {
            QImage leftImage = QImage(m_imageList.at(m_index)).scaled(503, 190);
            painter->drawImage(m_leftRect, getGrayImage(leftImage));
        }
        else if(m_animationType == Prev)
        {
            int leftIndex = (m_index + m_imageList.size() - 2) % m_imageList.size();
            QImage leftImage = QImage(m_imageList.at(leftIndex)).scaled(503, 190);
            painter->drawImage(m_leftRect, getGrayImage(leftImage));
        }
        else if(m_animationType == Jump)
        {
            int leftIndex = (m_index + m_imageList.size() - 1) % m_imageList.size();
            QImage leftImage = QImage(m_imageList.at(leftIndex)).scaled(503, 190);
            painter->drawImage(m_leftRect, getGrayImage(leftImage));
        }
    }

    painter->restore();
}

void Banner::drawCenter(QPainter *painter)
{
    painter->save();

    if(!m_isAnimation)
    {
        painter->drawImage(QRect(115, 0, 540, 200), QImage(m_imageList.at(m_index)));
    }
    else
    {
        if(m_animationType == Next)
        {
            int centerIndex = (m_index + m_imageList.size() + 1) % m_imageList.size();
            QImage centerImage = QImage(m_imageList.at(centerIndex));
            painter->drawImage(m_centerRect, centerImage);
        }
        else if(m_animationType == Prev)
        {
            int centerIndex = (m_index + m_imageList.size() - 1) % m_imageList.size();
            QImage centerImage = QImage(m_imageList.at(centerIndex));
            painter->drawImage(m_centerRect, centerImage);
        }
        else if(m_animationType == Jump)
        {
            painter->drawImage(m_centerRect, QImage(m_imageList.at(m_index)));
        }
    }

    painter->restore();
}

void Banner::drawRight(QPainter *painter)
{
    painter->save();

    if(!m_isAnimation)
    {
        int rightIndex = (m_index + m_imageList.size() + 1) % m_imageList.size();
        QImage rightImage = QImage(m_imageList.at(rightIndex)).scaled(503, 190);
        painter->drawImage(QRect(267, 10, 503, 190), getGrayImage(rightImage));
    }
    else
    {
        if(m_animationType == Next)
        {
            int rightIndex = (m_index + m_imageList.size() + 2) % m_imageList.size();
            QImage rightImage = QImage(m_imageList.at(rightIndex)).scaled(503, 190);
            painter->drawImage(m_rightRect, getGrayImage(rightImage));
        }
        else if (m_animationType == Prev)
        {
            QImage rightImage = QImage(m_imageList.at(m_index)).scaled(503, 190);
            painter->drawImage(m_rightRect, getGrayImage(rightImage));
        }
        else if (m_animationType == Jump)
        {
            int rightIndex = (m_index + m_imageList.size() + 1) % m_imageList.size();
            QImage rightImage = QImage(m_imageList.at(rightIndex)).scaled(503, 190);
            painter->drawImage(m_rightRect, getGrayImage(rightImage));
        }
    }

    painter->restore();
}

QImage Banner::getGrayImage(const QImage& image)
{
    int w = image.width();
    int h = image.height();

    QImage grayImage(w,h,QImage::Format_RGB32);

    for(int i = 0; i < w; ++i)
    {
        for(int j = 0; j < h; ++j)
        {
            QRgb pixel = image.pixel(i, j);
            int gray = qGray(pixel);
            QRgb grayPixel = qRgb(gray, gray, gray);
            grayImage.setPixel(i, j, grayPixel);
        }
    }

    return grayImage;
}

void Banner::valueChanged(const QVariant& value)
{
    QPropertyAnimation* object = (QPropertyAnimation*)(sender());

    if(object == m_leftAnimation)
    {
        qDebug() << "left " << value.toRect();
        m_leftRect = value.toRect();
    }
    else if(object == m_centerAnimation)
    {
        qDebug() << "Center " << value.toRect();
        m_centerRect = value.toRect();
    }
    else if(object == m_rightAnimation)
    {
        qDebug() << "Right " << value.toRect();
        m_rightRect = value.toRect();
    }

    update();
}

void Banner::finished()
{
    if(m_animationType == Next)
    {
        m_index = (m_index + 7 + 1) % 7;
    }
    else if(m_animationType == Prev)
    {
        m_index = (m_index + 7 - 1) % 7;
    }

    m_isAnimation = false;
}

