#include "flowlayout.h"

#include <algorithm>
#include <QWidget>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing) : QLayout(parent), x_hSpace(hSpacing), x_vSpace(vSpacing)
{
    m_lastHeight = -1;
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing) : x_hSpace(hSpacing), x_vSpace(vSpacing)
{
    m_lastHeight = -1;
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void FlowLayout::addItem(QLayoutItem *item)
{
    x_itemList.append(item);
}

void FlowLayout::setHorizontalSpacing(int hSpacing)
{
    if(hSpacing >= 0)
    {
        x_hSpace = hSpacing;
    }
}

int FlowLayout::horizontalSpacing() const
{
    if (x_hSpace >= 0)
    {
        return x_hSpace;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

void FlowLayout::setVerticalSpacing(int vSpacing)
{
    if(vSpacing >= 0)
    {
        x_vSpace = vSpacing;
    }
}

int FlowLayout::verticalSpacing() const
{
    if (x_vSpace >= 0)
    {
        return x_vSpace;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int FlowLayout::count() const
{
    return x_itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return x_itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    QLayoutItem* item = nullptr;

    if (index >= 0 && index < x_itemList.size())
    {
        item = x_itemList.takeAt(index);
        invalidate();
    }

    return item;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    Q_UNUSED(width)
    return -1;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    int height = doLayout(rect, false);

    if(height != m_lastHeight)
    {
//        emit sglHeightChange(height);
    }
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach(item, x_itemList)
        size = size.expandedTo(item->minimumSize());

    size += QSize(2 * margin(), 2 * margin());
    return size;
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    QLayoutItem *item;
    foreach(item, x_itemList)
    {
        QWidget *wid = item->widget();

        if(!wid->isHidden())
        {
            int spaceX = horizontalSpacing();
            if (spaceX == -1)
                spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
            int spaceY = verticalSpacing();
            if (spaceY == -1)
                spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);

            int nextX = x + item->sizeHint().width() + spaceX;
            if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
            {
                x = effectiveRect.x();
                y = y + lineHeight + spaceY;
                nextX = x + item->sizeHint().width() + spaceX;
                lineHeight = 0;
            }

            if (!testOnly)
                item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

            x = nextX;
            lineHeight = qMax(lineHeight, item->sizeHint().height());
        }
    }

    return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent)
    {
        return -1;
    }
    else if (parent->isWidgetType()) {
        QWidget *pw = qobject_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, 0, pw);
    }
    else {
        return static_cast<QLayout *>(parent)->spacing();
    }
}
