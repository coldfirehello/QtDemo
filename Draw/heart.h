#ifndef HEART_H
#define HEART_H

#include <QWidget>

class Heart : public QWidget
{
    Q_OBJECT

public:
    Heart(QWidget *parent = nullptr);
    ~Heart();

protected:
    void paintEvent(QPaintEvent *event) override;

};
#endif // HEART_H
