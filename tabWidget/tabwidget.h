#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

class FlowLayout;

class TabLabel : public QWidget
{
    Q_OBJECT

public:
    TabLabel(QWidget* parent = nullptr);
    ~TabLabel();

    void setWidget(QWidget* widget);

signals:
    void clicked();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QHBoxLayout* m_centerLayout;

private:
    void initUI();
};

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    enum TabPosition
    {
        North = 0,
        South,
        West,
        East
    };

public:
    TabWidget(QWidget* parent = nullptr);
    ~TabWidget();

    void addTab(QWidget* page, QWidget* label);
    void remove(int index);

    void setContentsMargins(const QMargins& margins);
    void setSpacing(int spacing);
    void setTabLabelSpacing(int spacing);
    void setTabPosition(TabPosition position);

private slots:
    void stackedWidgetChanged();

private:
    QGridLayout* m_mainLayout;
    FlowLayout* m_tabLayout;
    QStackedLayout* m_contentsLayout;
    QWidget* m_tabLabelWidget;
    TabPosition m_tabPosition;
    int m_spacing;

private:
    void initUI();
    void updateTabLabelWidget();
};
#endif // TABWIDGET_H
