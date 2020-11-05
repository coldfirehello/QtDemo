#include "tabwidget.h"
#include <QCursor>
#include <QDebug>
#include "flowlayout.h"

TabLabel::TabLabel(QWidget *parent) : QWidget(parent),
    m_centerLayout(nullptr)
{
    initUI();
}

TabLabel::~TabLabel()
{

}

void TabLabel::setWidget(QWidget *widget)
{
    if(widget != nullptr && m_centerLayout != nullptr)
    {
        m_centerLayout->addWidget(widget);
        resize(widget->size());
    }
}

void TabLabel::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    QCursor cursor;
    cursor.setShape(Qt::PointingHandCursor);

    setCursor(cursor);
}

void TabLabel::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);

    setCursor(cursor);
}

void TabLabel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit clicked();
}

void TabLabel::initUI()
{
    m_centerLayout = new QHBoxLayout();
    m_centerLayout->setMargin(0);
    m_centerLayout->setSpacing(0);

    setLayout(m_centerLayout);
}

TabWidget::TabWidget(QWidget *parent) : QWidget(parent),
    m_mainLayout(nullptr),
    m_tabLayout(nullptr),
    m_contentsLayout(nullptr),
    m_tabLabelWidget(nullptr),
    m_tabPosition(North),
    m_spacing(0)
{
    initUI();
}

TabWidget::~TabWidget()
{

}

void TabWidget::addTab(QWidget *page, QWidget *label)
{
    if(page != nullptr && label != nullptr && m_tabLayout != nullptr && m_contentsLayout != nullptr)
    {
        TabLabel* item = new TabLabel(this);
        item->setWidget(label);
        connect(label, &QWidget::destroyed, item, &TabWidget::deleteLater);
        connect(page, &QWidget::destroyed, item, &TabWidget::deleteLater);
        connect(item, &TabLabel::clicked, this, &TabWidget::stackedWidgetChanged);

        m_tabLayout->addWidget(item);

        updateTabLabelWidget();

        m_contentsLayout->addWidget(page);
    }
}

void TabWidget::remove(int index)
{
    if(m_contentsLayout != nullptr && m_tabLayout != nullptr && -1 < index && index < m_contentsLayout->count() && index < m_tabLayout->count())
    {
        QLayoutItem* label = m_tabLayout->takeAt(index);

        if(label != nullptr && label->widget() != nullptr)
        {
            m_tabLayout->removeItem(label);

            TabLabel* tabLabel = qobject_cast<TabLabel*>(label->widget());

            QWidget* childWidget = tabLabel->findChild<QWidget*>();
            childWidget->setParent(nullptr);

            delete tabLabel;
        }

        QLayoutItem* page = m_contentsLayout->takeAt(index);

        if(page != nullptr && page->widget() != nullptr)
        {
            m_contentsLayout->removeItem(page);

            page->widget()->setParent(nullptr);
        }
    }
}

void TabWidget::setContentsMargins(const QMargins &margins)
{
    if(m_mainLayout != nullptr && !margins.isNull())
    {
        m_mainLayout->setContentsMargins(margins);
    }
}

void TabWidget::setSpacing(int spacing)
{
    if(m_mainLayout != nullptr && spacing >= 0)
    {
        m_mainLayout->setSpacing(spacing);
    }
}

void TabWidget::setTabLabelSpacing(int spacing)
{
    if(m_tabLayout != nullptr && spacing >= 0)
    {
        m_spacing = spacing;

        if(m_tabPosition == North || m_tabPosition == South)
        {
            m_tabLayout->setVerticalSpacing(0);
            m_tabLayout->setHorizontalSpacing(spacing);
        }
        else
        {
            m_tabLayout->setVerticalSpacing(spacing);
            m_tabLayout->setHorizontalSpacing(0);
        }

        updateTabLabelWidget();
    }
}

void TabWidget::setTabPosition(TabWidget::TabPosition position)
{
    if(North <= position && position <= East)
    {
        m_tabPosition = position;

        Qt::Alignment align;
        int row = 0;
        int column = 0;

        if(position == North)
        {
            align = Qt::AlignLeft;
            row = 0;
            column = 1;
        }
        else if(position == South)
        {
            align = Qt::AlignLeft;
            row = 2;
            column = 1;
        }
        else if(position == West)
        {
            align = Qt::AlignTop;
            row = 1;
            column = 0;
        }
        else
        {
            align = Qt::AlignTop;
            row = 1;
            column = 2;
        }

        setTabLabelSpacing(m_spacing);

        m_mainLayout->removeWidget(m_tabLabelWidget);
        m_mainLayout->addWidget(m_tabLabelWidget, row, column, align);

        updateTabLabelWidget();
    }
}

void TabWidget::stackedWidgetChanged()
{
    TabLabel* label = qobject_cast<TabLabel*>(sender());

    if(label != nullptr && m_tabLayout != nullptr && m_contentsLayout != nullptr)
    {
        int index = m_tabLayout->indexOf(label);

        if(-1 < index && index < m_contentsLayout->count())
        {
            m_contentsLayout->setCurrentIndex(index);
        }
    }
}

void TabWidget::initUI()
{
    m_mainLayout = new QGridLayout();
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_tabLabelWidget = new QWidget(this);
    m_tabLabelWidget->setStyleSheet("QWidget{background:transparent;}");

    m_tabLayout = new FlowLayout(-1, 0, 0);
    m_tabLayout->setMargin(0);
    m_tabLabelWidget->setLayout(m_tabLayout);

    m_contentsLayout = new QStackedLayout();

    m_mainLayout->addWidget(m_tabLabelWidget, 0, 1, Qt::AlignLeft);
    m_mainLayout->addLayout(m_contentsLayout, 1, 1);

    setLayout(m_mainLayout);
}

void TabWidget::updateTabLabelWidget()
{
    if(m_tabLayout != nullptr && m_tabLabelWidget != nullptr)
    {
        int width = 0;
        int height = 0;
        int hSpacing = m_tabLayout->horizontalSpacing();
        int vSpacing = m_tabLayout->verticalSpacing();

        for(int i = 0; i < m_tabLayout->count(); ++i)
        {
            QLayoutItem* item = m_tabLayout->itemAt(i);

            if(item != nullptr && item->widget() != nullptr)
            {
                if(m_tabPosition == North || m_tabPosition == South)
                {
                    width += (item->widget()->width() + hSpacing);

                    height = item->widget()->height();
                }
                else
                {
                    height += (item->widget()->height() + vSpacing);

                    width = item->widget()->width();
                }
            }
        }

        if(width && height)
        {
            m_tabLabelWidget->setFixedSize(width, height);
        }
    }
}
