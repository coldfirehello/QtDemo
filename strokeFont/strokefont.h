#ifndef STROKEFONT_H
#define STROKEFONT_H

#include <QWidget>
#include <QFont>
#include <QPixmap>

class StrokeFont : public QWidget
{
    Q_OBJECT

public:
    StrokeFont(QWidget *parent = nullptr);
    ~StrokeFont();

    void setText(const QString& text);
    void setStrokeFont(const QColor& outLineColor, const QColor& fontColor, int fontWidth, int fontPixelSize, const QString& family = "");
    void setRotate(int angle);
    QPixmap strokeFontPixmap();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_fontPixelSize;
    QString m_text;
    QFont m_font;
    int m_contentWidth;
    int m_contenHeight;
    int m_fontWidth;
    int m_rotateAngle;
    QColor m_outLineColor;
    QColor m_contentColor;
    QPixmap m_strokeFontPixmap;

private:
    void updateStrokeFontPixmap();
    bool drawStrokeFontPixmap();
    QImage minSizeStrokenFontImage(const QImage& image);
};
#endif // STROKEFONT_H
