#ifndef AROUSEWIDGET_H
#define AROUSEWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class ArouseWidget : public QWidget
{
    Q_OBJECT

public:
    ArouseWidget(QWidget* parent = nullptr);
    ~ArouseWidget();

    void setUpWidget(QWidget* widget);
    void setDownWidget(QWidget* widget);
    void setDuration(int msecs);

public slots:
    void showArouseWidget();
    void hideArouseWidget();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QPropertyAnimation* m_downAnimation;
    QPropertyAnimation* m_upAnimation;
    QParallelAnimationGroup* m_arouseAnimationGroup;

    QWidget* m_downWidget;
    QWidget* m_upWidget;
    QWidget* m_downAnimationRegionWidget;
    QWidget* m_upAnimationRegionWidget;

private:
    void initUI();
    void updateUpAnimation();
    void updateDownAnimation();
};
#endif // AROUSEWIDGET_H
