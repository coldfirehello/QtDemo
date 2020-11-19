#ifndef BANNER_H
#define BANNER_H

#include <QWidget>
#include <QPixmap>
#include <QList>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>  //动画并行

class Banner : public QWidget
{
    Q_OBJECT
public:
    Banner(QWidget *parent = nullptr);
    ~Banner();

public:
    void addImage(const QString& image);

public slots:
    void next();
    void prev();
    void jump(int index);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void valueChanged(const QVariant& value);
    void finished();

private:
    enum AnimationType
    {
        UnKnow = -1,
        Next,
        Prev,
        Jump,
    };

    QStringList m_imageList;
    int m_index;
    bool m_isAnimation;
    QParallelAnimationGroup* m_animationGroup;
    QPropertyAnimation* m_leftAnimation;
    QPropertyAnimation* m_centerAnimation;
    QPropertyAnimation* m_rightAnimation;
    AnimationType m_animationType;
    QRect m_leftRect;
    QRect m_centerRect;
    QRect m_rightRect;

private:
    void drawLeft(QPainter* painter);
    void drawCenter(QPainter* painter);
    void drawRight(QPainter* painter);

    QImage getGrayImage(const QImage& image);
};
#endif // BANNER_H
