﻿#include "scatterflowers.h"
#include <QTime>
#include <QResizeEvent>
#include <QDebug>

ScatterFlowers::ScatterFlowers(QWidget *parent) : QWidget(parent),
    m_scatterFlowersAnimation(nullptr),
    m_animationGroup(nullptr),
    m_maxSideLength(20),
    m_animationTime(3000),
    m_graphicsCount(0),
    m_maxGraphicsCount(0)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    initUI();
}

ScatterFlowers::~ScatterFlowers()
{
    if(m_scatterFlowersAnimation != nullptr)
    {
        m_scatterFlowersAnimation->stop();
    }
}

void ScatterFlowers::startScatterFlowers()
{
    bool ret = true;
    updateGraphicsInfo();

    for (int i = 0; i < m_graphicsInfoMap.size(); i++)
    {
        GraphicsInfo info = m_graphicsInfoMap.value(i);

        if(info.scatterFlowersGraphics != nullptr)
        {
            info.scatterFlowersGraphics->setGraphicsHidden(true);
        }

        if(info.animation != nullptr && m_animationGroup != nullptr && info.isShow)
        {
            m_animationGroup->removeAnimation(info.animation);
            info.isShow = false;

            m_graphicsInfoMap[i] = info;
        }
    }

    for(int i = 0; i < m_graphicsCount; i++)
    {
        int index = randNumber(m_maxGraphicsCount);

        GraphicsInfo info = m_graphicsInfoMap.value(index);
        if(info.scatterFlowersGraphics != nullptr && info.animation != nullptr && m_animationGroup != nullptr)
        {
            info.startPoint = randGraphicsPos(true);
            info.endPoint = randGraphicsPos(false);

            info.scatterFlowersGraphics->setGraphicsHidden(false);
            info.isShow = true;

            info.animation->setKeyValueAt(0, QRect(info.startPoint.x(), info.startPoint.y(), info.scatterFlowersGraphics->width(), info.scatterFlowersGraphics->height()));
            info.animation->setKeyValueAt(1, QRect(info.endPoint.x(), info.endPoint.y(), info.scatterFlowersGraphics->width(), info.scatterFlowersGraphics->height()));

            m_animationGroup->addAnimation(info.animation);

            m_graphicsInfoMap[index] = info;
        }
        else
        {
            ret = false;
        }
    }

    if(ret && m_animationGroup != nullptr)
    {
        m_animationGroup->start();
    }
    else
    {
        qDebug() << __FUNCTION__ << "Scatter Flowers is fail";
    }
}

void ScatterFlowers::stopScatterFlowers()
{
    m_scatterFlowersAnimation->stop();
}

void ScatterFlowers::resizeEvent(QResizeEvent *event)
{
    updateGraphicsInfo();
}

void ScatterFlowers::initUI()
{
    resize(400, 400);

    m_graphicsCount = graphicsCount();

    m_scatterFlowersAnimation = new QPropertyAnimation(this, "geometry", this);
    m_scatterFlowersAnimation->setDuration(m_animationTime);
    m_scatterFlowersAnimation->setEasingCurve(QEasingCurve::OutQuad);

    m_animationGroup = new QParallelAnimationGroup(this);
}

int ScatterFlowers::randNumber(int range)
{
    return rand() % range;
}

ScatterFlowersGraphics::GraphicsType ScatterFlowers::randGraphics()
{
    ScatterFlowersGraphics::GraphicsType ret = ScatterFlowersGraphics::Rect;

    return ret;
}

qreal ScatterFlowers::randAngle()
{
    const int kAngleRange = 90;

    qreal ret = static_cast<qreal>(randNumber(kAngleRange));

    return ret;
}

QColor ScatterFlowers::randColor()
{
    const int kColorRange = 255;

    QColor ret(randNumber(kColorRange),randNumber(kColorRange),randNumber(kColorRange));

    return ret;
}

int ScatterFlowers::randSideLength()
{
    const int kMinSideLength = 10;

    int sideLength = randNumber(m_maxSideLength);

    if(sideLength < kMinSideLength)
    {
        sideLength = kMinSideLength;
    }

    int ret = sideLength;

    return ret;
}

QPoint ScatterFlowers::randGraphicsPos(bool isStart)
{
    QPoint ret;

    int w = this->width();
    int h = this->height();

    if(isStart)
    {
        int x = randNumber(w);
        int y = randNumber(h) - h;

        ret.setX(x);
        ret.setY(y);
    }
    else
    {
        int x = randNumber(2 * w);
        int y = randNumber(h);

        x = x - w * 0.5;
        y = y + h;

        ret.setX(x);
        ret.setY(y);
    }

    return ret;
}

void ScatterFlowers::updateGraphicsInfo()
{
    m_graphicsCount = graphicsCount();

    int size = m_graphicsInfoMap.size();
    int diff = m_maxGraphicsCount - size;

    if(diff > 0)
    {
        for(int i = 0; (i < diff) && (m_animationGroup != nullptr); ++i)
        {
            GraphicsInfo info;

            info.startPoint = randGraphicsPos(true);
            info.endPoint = randGraphicsPos(false);

            QColor color(randNumber(255),randNumber(255),randNumber(255));

            info.drawGraphicsinfo.type = randGraphics();
            info.drawGraphicsinfo.angle = randAngle();
            info.drawGraphicsinfo.color = randColor();
            info.drawGraphicsinfo.sideLength = randSideLength();

            ScatterFlowersGraphics* scatterFlowersGraphics = ScatterFlowersGraphics::getGraphics(info.drawGraphicsinfo, this);
            scatterFlowersGraphics->setGraphicsHidden(true);
            scatterFlowersGraphics->setMaxSideLength(m_maxSideLength);
            scatterFlowersGraphics->move(info.startPoint);

            info.scatterFlowersGraphics = scatterFlowersGraphics;

            QPropertyAnimation* animation = new QPropertyAnimation(scatterFlowersGraphics, "geometry", this);
            animation->setDuration(m_animationTime);
            info.animation = animation;

            m_graphicsInfoMap[size + i] = info;
        }
    }
    else
    {
        diff = -diff;

        while (diff)
        {
            GraphicsInfo info = m_graphicsInfoMap.value(size - 1 - diff);

            if(info.scatterFlowersGraphics != nullptr)
            {
                info.scatterFlowersGraphics->setGraphicsHidden(true);
            }
            else
            {
                qDebug() << __FUNCTION__ << "Update graphics info is fail";
                break;
            }

            diff--;
        }
    }
}

int ScatterFlowers::graphicsCount()
{
    const int kDilutionRatio = 20;  //稀释20倍
    const int kMaxGraphicsCount = 60;   //最大数量60

    int ret = 0;

    m_maxGraphicsCount = this->width() * this->height() / (m_maxSideLength * m_maxSideLength * kDilutionRatio);

    ret = m_maxGraphicsCount * 0.618;   //黄金比例

    ret = (ret > kMaxGraphicsCount) ? kMaxGraphicsCount : ret;

    return ret;
}
