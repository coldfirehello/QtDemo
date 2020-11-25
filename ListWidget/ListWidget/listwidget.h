#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = nullptr);
    ~ListWidget();

    void addWidget(QWidget* item);
    void insert(int row, QWidget* item);
    void remove(QWidget* item);
    void remove(int row);
    QWidget* takeWidget(int row);
    void clear();
    int count() const;

    void setVerticalSpacing(int spacing);
    void setContentsMargins(const QMargins &margins);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QScrollArea* m_scrollArea;
    QWidget* m_scrollWidget;
    QVBoxLayout* m_scrollLayout;

private:
    void initUI();
};
#endif // LISTWIDGET_H
