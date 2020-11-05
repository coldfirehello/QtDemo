#include "tabwidget.h"

#include <QApplication>
#include <QLabel>

QWidget* createLabel(const QString& text)
{
    QWidget* ret = nullptr;

    if(!text.isEmpty())
    {
        ret = new QWidget();
        ret->setFixedSize(36, 33);

        QLabel* label = new QLabel(ret);
        label->setText(text);
        label->setStyleSheet("QLabel{color:#333333;font-size:18px;font-style:normal;font-weight:normal;}");

        QLabel* lineLabel = new QLabel(ret);
        lineLabel->setFixedSize(28, 4);
        lineLabel->setStyleSheet("QLabel{background:#1ED278;border-radius:2px;}");

        QVBoxLayout* layout = new QVBoxLayout(ret);
        layout->setMargin(0);
        layout->setSpacing(8);
        layout->addWidget(label);
        layout->addWidget(lineLabel, 0, Qt::AlignHCenter);
    }

    return ret;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget* label = createLabel(QStringLiteral("目录"));

    QWidget* page = new QWidget();
    page->setStyleSheet("QWidget{background:red;}");

    QLabel* pageLabel = new QLabel(page);
    pageLabel->setText("0000000000");


    QWidget* label1 = createLabel(QStringLiteral("学习"));

    QWidget* page1 = new QWidget();
    page1->setStyleSheet("QWidget{background:blue;}");
    QLabel* pageLabel1 = new QLabel(page1);
    pageLabel1->setText("111111111111");

    QWidget* label2 = createLabel(QStringLiteral("错题"));

    QWidget* page2 = new QWidget();
    page2->setStyleSheet("QWidget{background:green;}");
    QLabel* pageLabel2 = new QLabel(page2);
    pageLabel2->setText("222222222222");


    TabWidget w;
    w.setTabLabelSpacing(32);
    w.addTab(page, label);
    w.addTab(page1, label1);
    w.addTab(page2, label2);
    w.setTabPosition(TabWidget::North);
    w.setSpacing(20);
    w.show();

    return a.exec();
}
