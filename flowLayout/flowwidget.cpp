#include "flowwidget.h"
#include <QPushButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>
#include "flowlayout.h"

#define FLOWLAYOUT
//#define LISTWIDGET

FlowWidget::FlowWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton* btn = new QPushButton("btn");
    btn->setObjectName("btn");
    connect(btn, &QPushButton::clicked, this, &FlowWidget::onBtn);
    QPushButton* btn1 = new QPushButton("btn1");
    btn1->setObjectName("btn1");
    connect(btn1, &QPushButton::clicked, this, &FlowWidget::onBtn);
    QPushButton* btn2 = new QPushButton("btn2");
    btn2->setObjectName("btn2");
    connect(btn2, &QPushButton::clicked, this, &FlowWidget::onBtn);
    QPushButton* btn3 = new QPushButton("btn3");
    btn3->setObjectName("btn3");
    connect(btn3, &QPushButton::clicked, this, &FlowWidget::onBtn);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(btn);
    hLayout->addWidget(btn1);
    hLayout->addWidget(btn2);
    hLayout->addWidget(btn3);

#ifdef LISTWIDGET
    m_list.setViewMode(QListView::IconMode);
    m_list.setResizeMode(QListView::Adjust);
    m_list.setMovement(QListView::Static);
    m_list.setSpacing(10);
#endif

#ifdef FLOWLAYOUT
    FlowLayout* flowLayout = new FlowLayout(-1, 12, 20);
#endif

    m_Item1 = new QListWidgetItem();
    m_btn1 = new QPushButton("1");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn1);
#endif
#ifdef LISTWIDGET
    m_Item1->setSizeHint(QSize(100, 100));
    m_list.addItem(m_Item1);
    m_list.setItemWidget(m_Item1, m_btn1);
#endif

    m_Item2 = new QListWidgetItem();
    m_btn2 = new QPushButton("2");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn2);
#endif
#ifdef LISTWIDGET
    m_Item2->setSizeHint(QSize(100, 100));
    m_list.addItem(m_Item2);
    m_list.setItemWidget(m_Item2, m_btn2);
#endif

    m_Item3 = new QListWidgetItem();
    m_btn3 = new QPushButton("3");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn3);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item3);
    m_Item3->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item3, m_btn3);
#endif

    m_Item4 = new QListWidgetItem();
    m_btn4 = new QPushButton("4");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn4);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item4);
    m_Item4->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item4, m_btn4);
#endif

    m_Item5 = new QListWidgetItem();
    m_btn5 = new QPushButton("5");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn5);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item5);
    m_Item5->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item5, m_btn5);
#endif

    m_Item6 = new QListWidgetItem();
    m_btn6 = new QPushButton("6");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn6);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item6);
    m_Item6->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item6, m_btn6);
#endif

    m_Item7 = new QListWidgetItem();
    m_btn7 = new QPushButton("7");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn7);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item7);
    m_Item7->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item7, m_btn7);
#endif

    m_Item8 = new QListWidgetItem();
    m_btn8 = new QPushButton("8");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn8);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item8);
    m_Item8->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item8, m_btn8);
#endif

    m_Item9 = new QListWidgetItem();
    m_btn9 = new QPushButton("9");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btn9);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_Item9);
    m_Item9->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_Item9, m_btn9);
#endif

    m_ItemA = new QListWidgetItem();
    m_btnA = new QPushButton("A");
#ifdef FLOWLAYOUT
    flowLayout->addWidget(m_btnA);
#endif
#ifdef LISTWIDGET
    m_list.addItem(m_ItemA);
    m_ItemA->setSizeHint(QSize(100, 100));
    m_list.setItemWidget(m_ItemA, m_btnA);
#endif

#ifdef FLOWLAYOUT
    QWidget* flowWidget = new QWidget();
    flowWidget->setLayout(flowLayout);
#endif
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(hLayout);
#ifdef LISTWIDGET
    layout->addWidget(&m_list);
#endif
#ifdef FLOWLAYOUT
    layout->addWidget(flowWidget);
#endif
    setLayout(layout);
}

void FlowWidget::onBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn->objectName() == "btn")
    {
#ifdef LISTWIDGET
        m_Item1->setHidden(false);
        m_Item2->setHidden(false);
        m_Item3->setHidden(false);
        m_Item4->setHidden(false);
        m_Item5->setHidden(false);
        m_Item6->setHidden(false);
        m_Item7->setHidden(false);
        m_Item8->setHidden(false);
        m_Item9->setHidden(false);
        m_ItemA->setHidden(false);
        m_list.update();
#endif
#ifdef FLOWLAYOUT
        m_btn1->setHidden(false);
        m_btn2->setHidden(false);
        m_btn3->setHidden(false);
        m_btn4->setHidden(false);
        m_btn5->setHidden(false);
        m_btn6->setHidden(false);
        m_btn7->setHidden(false);
        m_btn8->setHidden(false);
        m_btn9->setHidden(false);
        m_btnA->setHidden(false);
#endif
    }
    else if(btn->objectName() == "btn1")
    {
#ifdef LISTWIDGET
        m_Item1->setHidden(true);
        m_Item2->setHidden(true);
        m_Item3->setHidden(false);
        m_Item4->setHidden(false);
        m_Item5->setHidden(true);
        m_Item6->setHidden(true);
        m_Item7->setHidden(true);
        m_Item8->setHidden(false);
        m_Item9->setHidden(false);
        m_ItemA->setHidden(false);
        m_list.update();
#endif
#ifdef FLOWLAYOUT
        m_btn1->setHidden(true);
        m_btn2->setHidden(true);
        m_btn3->setHidden(false);
        m_btn4->setHidden(false);
        m_btn5->setHidden(true);
        m_btn6->setHidden(true);
        m_btn7->setHidden(true);
        m_btn8->setHidden(false);
        m_btn9->setHidden(false);
        m_btnA->setHidden(false);
#endif
    }
    else if(btn->objectName() == "btn2")
    {
#ifdef LISTWIDGET
        m_Item1->setHidden(false);
        m_Item2->setHidden(false);
        m_Item3->setHidden(true);
        m_Item4->setHidden(true);
        m_Item5->setHidden(false);
        m_Item6->setHidden(false);
        m_Item7->setHidden(true);
        m_Item8->setHidden(false);
        m_Item9->setHidden(true);
        m_ItemA->setHidden(false);
        m_list.update();
#endif
#ifdef FLOWLAYOUT
        m_btn1->setHidden(false);
        m_btn2->setHidden(false);
        m_btn3->setHidden(true);
        m_btn4->setHidden(true);
        m_btn5->setHidden(false);
        m_btn6->setHidden(false);
        m_btn7->setHidden(true);
        m_btn8->setHidden(false);
        m_btn9->setHidden(true);
        m_btnA->setHidden(false);
#endif
    }
    else
    {
#ifdef LISTWIDGET
        m_Item1->setHidden(false);
        m_Item2->setHidden(false);
        m_Item3->setHidden(false);
        m_Item4->setHidden(false);
        m_Item5->setHidden(true);
        m_Item6->setHidden(true);
        m_Item7->setHidden(true);
        m_Item8->setHidden(false);
        m_Item9->setHidden(false);
        m_ItemA->setHidden(false);
        m_list.update();
#endif
#ifdef FLOWLAYOUT
        m_btn1->setHidden(false);
        m_btn2->setHidden(false);
        m_btn3->setHidden(false);
        m_btn4->setHidden(false);
        m_btn5->setHidden(true);
        m_btn6->setHidden(true);
        m_btn7->setHidden(true);
        m_btn8->setHidden(false);
        m_btn9->setHidden(false);
        m_btnA->setHidden(false);
#endif
    }
}
