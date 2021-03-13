#ifndef TWEENEDANIMATION_H
#define TWEENEDANIMATION_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPixmap>

class TweenedAnimation : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal widgetOpacity READ widgetOpacity WRITE setWidgetOpacity)

public:
    enum Direction
    {
        Invalid = -1,
        Forward,
        Backward
    };

public:
    TweenedAnimation(QWidget *parent = nullptr);
    ~TweenedAnimation();

    void setTweenedAnimationWidget(QWidget* widget);

    void start();
    void stop();

    void setDuration(int msecs);
    int duration() const;

    void setDirection(Direction direction);
    Direction direction() const;

    QVariant startValue() const;
    void setStartValue(const QVariant& value);

    QVariant endValue() const;
    void setEndValue(const QVariant& value);

    void setLoopCount(int loopCount);
    int loopCount() const;

    bool setWidgetOpacity(qreal opacity);
    qreal widgetOpacity();

signals:
    void finished();
    void stateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void currentLoopChanged(int currentLoop);
    void directionChanged(QAbstractAnimation::Direction);
    void valueChanged(const QVariant& value);

private:
    QPixmap m_animationWidgetPixmap;
    qreal m_opacity;

    QLabel* m_animationTargetLabel;
    QPropertyAnimation* m_propertyAnimation;
    QWidget* m_tweenedTargetWidget;

private:
    void initUI();
    void updateAnimationWidgetPixmap();
};
#endif // TWEENEDANIMATION_H
