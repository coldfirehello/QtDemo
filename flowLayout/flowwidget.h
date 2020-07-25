#ifndef FLOWWIDGET_H
#define FLOWWIDGET_H

#include <QListWidget>
#include <QPushButton>

class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = nullptr);

signals:

private slots:
    void onBtn();

private:
    QListWidget m_list;

    QListWidgetItem* m_Item1;
    QListWidgetItem* m_Item2;
    QListWidgetItem* m_Item3;
    QListWidgetItem* m_Item4;
    QListWidgetItem* m_Item5;
    QListWidgetItem* m_Item6;
    QListWidgetItem* m_Item7;
    QListWidgetItem* m_Item8;
    QListWidgetItem* m_Item9;
    QListWidgetItem* m_ItemA;

    QPushButton* m_btn1;
    QPushButton* m_btn2;
    QPushButton* m_btn3;
    QPushButton* m_btn4;
    QPushButton* m_btn5;
    QPushButton* m_btn6;
    QPushButton* m_btn7;
    QPushButton* m_btn8;
    QPushButton* m_btn9;
    QPushButton* m_btnA;
};

#endif // FLOWWIDGET_H
