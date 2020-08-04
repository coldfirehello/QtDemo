#ifndef ScatterFlowers_H
#define ScatterFlowers_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMap>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "scatterflowersgraphics.h"

class ScatterFlowers : public QWidget
{
    Q_OBJECT     

public:
    ScatterFlowers(QWidget *parent = nullptr);
    ~ScatterFlowers();

    void startScatterFlowers();
    void stopScatterFlowers();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    struct GraphicsInfo
    {
        QPoint startPoint;
        QPoint endPoint;
        bool isShow;
        ScatterFlowersGraphics::DrawGraphicsInfo drawGraphicsinfo;
        ScatterFlowersGraphics* scatterFlowersGraphics;
        QPropertyAnimation* animation;

        GraphicsInfo() : startPoint(0,0), endPoint(0,0), isShow(false), scatterFlowersGraphics(nullptr) {}
    };

private:
    void initUI();
    int randNumber(int range);
    ScatterFlowersGraphics::GraphicsType randGraphics();
    qreal randAngle();
    QColor randColor();
    int randSideLength();
    QPoint randGraphicsPos(bool isStart);

    void updateGraphicsInfo();
    int graphicsCount();

private:
    QPropertyAnimation* m_scatterFlowersAnimation;
    QMap<int, GraphicsInfo> m_graphicsInfoMap;
    QParallelAnimationGroup* m_animationGroup;

    const int m_maxSideLength;
    const int m_animationTime;
    int m_graphicsCount;
    int m_maxGraphicsCount;
};

#endif // ScatterFlowers_H
