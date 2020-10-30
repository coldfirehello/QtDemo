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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const int m_drawXoffset;
    int m_fontPixelSize;
    QString m_text;
    QFont m_font;
    int m_contentWidth;
    int m_fontWidth;
    int m_fontHeight;
    int m_rotateAngle;
    int m_rotateOffsetLength;
    QColor m_outLineColor;
    QColor m_contentColor;
    QPixmap m_strokeFontPixmap;

private:
    void updateStrokeFontPixmap();
    bool drawStrokeFontPixmap();
    QSize minSize(int fontWidth, int fontHeight, int angle);
};
#endif // STROKEFONT_H
