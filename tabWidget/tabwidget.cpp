#include "tabwidget.h"

TabLabel::TabLabel(QWidget *parent) : QPushButton(parent),
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
        setFixedSize(widget->size());
    }
}

void TabLabel::initUI()
{
    m_centerLayout = new QHBoxLayout();
    m_centerLayout->setMargin(0);
    m_centerLayout->setSpacing(0);

    setLayout(m_centerLayout);
    setStyleSheet("QPushButton{background:transparent;border:none;padding:0px;}");
    setCursor(Qt::PointingHandCursor);
}

TabWidget::TabWidget(QWidget *parent) : QWidget(parent),
    m_mainLayout(nullptr),
    m_tabLayout(nullptr),
    m_contentsLayout(nullptr),
    m_contentsStackedLayout(nullptr),
    m_tabLabelBackgroundWidget(nullptr),
    m_tabLabelBackgroundHLayout(nullptr),
    m_tabLabelBackgroundVLayout(nullptr),
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
    if(page != nullptr && label != nullptr && m_tabLayout != nullptr && m_contentsStackedLayout != nullptr)
    {
        TabLabel* item = new TabLabel(this);
        item->setWidget(label);
        connect(label, &QWidget::destroyed, item, &TabWidget::deleteLater);
        connect(page, &QWidget::destroyed, item, &TabWidget::deleteLater);
        connect(item, &TabLabel::clicked, this, &TabWidget::stackedWidgetChanged);

        m_tabLayout->addWidget(item);

        updateTabLabelWidget();

        m_contentsStackedLayout->addWidget(page);
    }
}

void TabWidget::remove(int index)
{
    if(m_contentsStackedLayout != nullptr && m_tabLayout != nullptr && -1 < index && index < m_contentsStackedLayout->count() && index < m_tabLayout->count())
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

        QLayoutItem* page = m_contentsStackedLayout->takeAt(index);

        if(page != nullptr && page->widget() != nullptr)
        {
            m_contentsStackedLayout->removeItem(page);

            page->widget()->setParent(nullptr);
        }
    }
}

void TabWidget::setContentsMargins(const QMargins &margins)
{
    if(m_contentsLayout != nullptr && !margins.isNull())
    {
        m_contentsLayout->setContentsMargins(margins);
    }
}

void TabWidget::setLabelMargins(const QMargins &margins)
{
    if(m_tabPosition == North || m_tabPosition == South)
    {
        m_tabLabelBackgroundHLayout->setContentsMargins(margins);
        m_tabLabelBackgroundVLayout->setMargin(0);
    }
    else
    {
        m_tabLabelBackgroundVLayout->setContentsMargins(margins);
        m_tabLabelBackgroundHLayout->setMargin(0);
    }
}

void TabWidget::setSpacing(int spacing)
{
    if(m_mainLayout != nullptr && spacing >= 0)
    {
        m_mainLayout->setSpacing(spacing);
    }
}

int TabWidget::spacing()
{
    int ret = -1;

    if(m_mainLayout != nullptr)
    {
        ret = m_mainLayout->spacing();
    }

    return ret;
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

//        Qt::Alignment align;
        int row = 0;
        int column = 0;

        if(position == North)
        {
//            align = Qt::AlignLeft;
            row = 0;
            column = 1;
        }
        else if(position == South)
        {
//            align = Qt::AlignLeft;
            row = 2;
            column = 1;
        }
        else if(position == West)
        {
//            align = Qt::AlignTop;
            row = 1;
            column = 0;
        }
        else
        {
//            align = Qt::AlignTop;
            row = 1;
            column = 2;
        }

        setTabLabelSpacing(m_spacing);

        m_mainLayout->removeWidget(m_tabLabelBackgroundWidget);
        m_mainLayout->addWidget(m_tabLabelBackgroundWidget, row, column/*, align*/);

        updateTabLabelWidget();
    }
}

void TabWidget::setTabLabelStyleSheet(const QString& styleSheet)
{
    if(m_tabLabelBackgroundWidget != nullptr && !styleSheet.isEmpty())
    {
        m_tabLabelBackgroundWidget->setStyleSheet(styleSheet);
    }
}

int TabWidget::currentIndex() const
{
    int ret = -1;

    if(m_contentsStackedLayout != nullptr)
    {
        ret = m_contentsStackedLayout->currentIndex();
    }

    return ret;
}

void TabWidget::setCurrentIndex(int index)
{
    if(m_contentsStackedLayout != nullptr)
    {
        m_contentsStackedLayout->setCurrentIndex(index);
    }
}

void TabWidget::stackedWidgetChanged()
{
    TabLabel* label = qobject_cast<TabLabel*>(sender());

    if(label != nullptr && m_tabLayout != nullptr && m_contentsStackedLayout != nullptr)
    {
        int index = m_tabLayout->indexOf(label);

        if(-1 < index && index < m_contentsStackedLayout->count())
        {
            m_contentsStackedLayout->setCurrentIndex(index);
            emit currentChanged(index);
        }
    }
}

void TabWidget::initUI()
{
    m_mainLayout = new QGridLayout();
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_tabLabelBackgroundWidget = new QWidget();
    m_tabLabelBackgroundWidget->setStyleSheet("QWidget{background:transparent;}");

    m_tabLabelBackgroundHLayout = new QHBoxLayout();
    m_tabLabelBackgroundHLayout->setMargin(0);
    m_tabLabelBackgroundHLayout->setSpacing(0);

    m_tabLabelBackgroundVLayout = new QVBoxLayout();
    m_tabLabelBackgroundVLayout->setMargin(0);
    m_tabLabelBackgroundVLayout->setSpacing(0);

    m_tabLabelWidget = new QWidget(m_tabLabelBackgroundWidget);
    m_tabLabelWidget->setStyleSheet("QWidget{background:transparent;}");

    m_tabLayout = new FlowLayout(-1, 0, 0);
    m_tabLayout->setMargin(0);
    m_tabLabelWidget->setLayout(m_tabLayout);

    m_tabLabelBackgroundHLayout->addWidget(m_tabLabelWidget);
    m_tabLabelBackgroundHLayout->addStretch();

    m_tabLabelBackgroundVLayout->addLayout(m_tabLabelBackgroundHLayout);
    m_tabLabelBackgroundVLayout->addStretch();

    m_tabLabelBackgroundWidget->setLayout(m_tabLabelBackgroundVLayout);

    m_contentsLayout = new QHBoxLayout();
    m_contentsLayout->setMargin(0);
    m_contentsLayout->setSpacing(0);

    m_contentsStackedLayout = new QStackedLayout();
    m_contentsLayout->addLayout(m_contentsStackedLayout);

    m_mainLayout->addWidget(m_tabLabelBackgroundWidget, 0, 1);
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

            if(m_tabPosition == North || m_tabPosition == South)
            {
                m_tabLabelBackgroundWidget->setFixedHeight(height);
            }
            else
            {
                m_tabLabelBackgroundWidget->setFixedWidth(width);
            }
        }
    }
}
