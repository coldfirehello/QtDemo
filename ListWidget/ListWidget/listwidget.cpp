#include "listwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QScrollBar>

ListWidget::ListWidget(QWidget *parent) : QWidget(parent),
    m_scrollArea(nullptr),
    m_scrollWidget(nullptr),
    m_scrollLayout(nullptr)
{
    initUI();
}

ListWidget::~ListWidget()
{

}

void ListWidget::addWidget(QWidget *item)
{
    if(item != nullptr && m_scrollLayout != nullptr)
    {
        m_scrollLayout->addWidget(item);
    }
}

void ListWidget::insert(int row, QWidget *item)
{
    if(item != nullptr)
    {
        if(row < 0)
        {
            row = 0;
        }

        if(row > count())
        {
            row = count();
        }

        m_scrollLayout->insertWidget(row, item);
    }
}

void ListWidget::remove(QWidget *item)
{
    if(item != nullptr && m_scrollLayout != nullptr)
    {
        int index = m_scrollLayout->indexOf(item);

        if(-1 != index)
        {
            QWidget* widget = takeWidget(index);

            if(widget == item)
            {
                delete widget;
            }
        }
    }
}

QWidget *ListWidget::takeWidget(int row)
{
    QWidget* ret = nullptr;

    QLayoutItem* item = m_scrollLayout->takeAt(row);

    if(0 != item)
    {
        ret = item->widget();
    }

    return ret;
}

void ListWidget::clear()
{
    if(m_scrollLayout != nullptr)
    {
        while (count())
        {
            QLayoutItem* item = m_scrollLayout->takeAt(count() - 1);

            if(item != nullptr && item->widget() != nullptr)
            {
                delete  item->widget();
            }
        }
    }
}

int ListWidget::count() const
{
    int ret = 0;

    if(m_scrollLayout != nullptr)
    {
        ret = m_scrollLayout->count();
    }

    return ret;
}

void ListWidget::setVerticalSpacing(int spacing)
{
    if(m_scrollLayout != nullptr)
    {
        m_scrollLayout->setSpacing(spacing);
    }
}

void ListWidget::setContentsMargins(const QMargins &margins)
{
    m_scrollLayout->setContentsMargins(margins);
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    if(m_scrollLayout != nullptr)
    {
        int left = 0;
        int right = 0;
        int top = 0;
        int bottom = 0;

        m_scrollLayout->getContentsMargins(&left, &top, &right, &bottom);


        m_scrollWidget->setFixedWidth(width());
        m_scrollWidget->setFixedHeight(m_scrollArea->height() * 1.5);
    }
}

void ListWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption option;
    option.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ListWidget::initUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_scrollLayout = new QVBoxLayout();
    m_scrollLayout->setContentsMargins(10, 10, 0, 10);
    m_scrollLayout->setSpacing(10);

    m_scrollWidget = new QWidget(this);
    m_scrollWidget->setStyleSheet("QWidget{background:black;}");
    m_scrollWidget->setLayout(m_scrollLayout);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setStyleSheet("QScrollArea{background:black;}");
    m_scrollArea->setMouseTracking(true);
    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollArea->setStyleSheet("border:none;");
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->verticalScrollBar()->setStyleSheet(QStringLiteral("QScrollBar:vertical {"
                                                                    "width:%2px;"
                                                                    "padding-right:2px;"
                                                                    "background: rgba(0,0,0,0);"
                                                                    "margin: 0px 0px 0px 0px;"
                                                                    "border-radius: %1px;"
                                                                    "border: none;}"
                                                                    "QScrollBar::handle:vertical {"
                                                                    "background: rgba(255, 255, 255, 0.7);"
                                                                    "border-radius: %1px;"
                                                                    "border: none;"
                                                                    "}"
                                                                    "QScrollBar::handle:vertical:hover {"
                                                                    "background: rgba(255, 255, 255, 0.7);"
                                                                    "margin: 0px 0px 0px 0px;"
                                                                    "border-radius: %1px;"
                                                                    "border: none;"
                                                                    "}"
                                                                    "QScrollBar::handle:vertical:pressed {"
                                                                    "background: rgba(255, 255, 255, 0.7);"
                                                                    "margin: 0px 0px 0px 0px;"
                                                                    "border-radius: %1px;"
                                                                    "border: none;"
                                                                    "}"
                                                                    "QScrollBar::add-line:vertical {"
                                                                    "background: transparent;"
                                                                    "height: 0px;"
                                                                    "subcontrol-position: bottom;"
                                                                    "subcontrol-origin: margin;"
                                                                    "}"
                                                                    "QScrollBar::sub-line:vertical {"
                                                                    "background: transparent;"
                                                                    "height: 0px;"
                                                                    "subcontrol-position: top;"
                                                                    "subcontrol-origin: margin;"
                                                                    "}"
                                                                    "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                                                    "border: 1px solid grey;"
                                                                    "width: %1px;"
                                                                    "height: %1px;"
                                                                    "background: white;"
                                                                    "}"
                                                                    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                                                    "background: none;}")
                                                     .arg((int)(2)).arg(6));

    mainLayout->addWidget(m_scrollArea);

    setLayout(mainLayout);
}

