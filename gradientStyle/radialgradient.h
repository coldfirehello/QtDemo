#ifndef RADIALGRADIENT_H
#define RADIALGRADIENT_H

#include <QWidget>

class RadialGradient : public QWidget
{
    Q_OBJECT

public:
    RadialGradient(QWidget *parent = nullptr);
    ~RadialGradient();
};
#endif // RADIALGRADIENT_H
