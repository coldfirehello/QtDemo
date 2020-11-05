﻿#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>

#include <QLayout>
#include <QRect>
#include <QStyle>

class FlowLayout : public QLayout
{
    Q_OBJECT
public:
    explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    FlowLayout(int margin, int hSpacing, int vSpacing);
    ~FlowLayout();

    void addItem(QLayoutItem *item) Q_DECL_OVERRIDE;
    void setHorizontalSpacing(int hSpacing);
    int horizontalSpacing() const;
    void setVerticalSpacing(int vSpacing);
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
    bool hasHeightForWidth() const Q_DECL_OVERRIDE;
    int heightForWidth(int) const Q_DECL_OVERRIDE;
    int count() const Q_DECL_OVERRIDE;
    QLayoutItem *itemAt(int index) const Q_DECL_OVERRIDE;
    QSize minimumSize() const Q_DECL_OVERRIDE;
    void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QLayoutItem *takeAt(int index) Q_DECL_OVERRIDE;

signals:
//    void sglHeightChange(int height);

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

private:
    QList<QLayoutItem *> x_itemList;
    int x_hSpace;
    int x_vSpace;
    int m_lastHeight;
};
#endif
