#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "flowlayout.h"

class TabLabel : public QPushButton
{
    Q_OBJECT

public:
    TabLabel(QWidget* parent = nullptr);
    ~TabLabel();

    void setWidget(QWidget* widget);

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
    void setLabelMargins(const QMargins& margins);
    void setSpacing(int spacing);
    int spacing();
    void setTabLabelSpacing(int spacing);
    void setTabPosition(TabPosition position);
    void setTabLabelStyleSheet(const QString& styleSheet);
    int currentIndex() const;
    void setCurrentIndex(int index);

signals:
    void currentChanged(int index);

private slots:
    void stackedWidgetChanged();

private:
    QGridLayout* m_mainLayout;
    FlowLayout* m_tabLayout;
    QHBoxLayout* m_contentsLayout;
    QStackedLayout* m_contentsStackedLayout;
    QWidget* m_tabLabelBackgroundWidget;
    QHBoxLayout* m_tabLabelBackgroundHLayout;
    QVBoxLayout* m_tabLabelBackgroundVLayout;
    QWidget* m_tabLabelWidget;
    TabPosition m_tabPosition;
    int m_spacing;

private:
    void initUI();
    void updateTabLabelWidget();
};
#endif // TABWIDGET_H
