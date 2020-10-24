#ifndef HDICON_H
#define HDICON_H

#include <QLabel>

class HDIcon : public QLabel
{
    Q_OBJECT

public:
    HDIcon(QWidget *parent = nullptr);
    ~HDIcon();

    void setIconInfo(const QString& filePath, const QSize& scaledSize, int radius = 0);

private:
    QPixmap pixmapToRound(const QString& filePath, const QSize& scaledSize, int radius = 0);
};
#endif // HDICON_H
