﻿#ifndef STROKEFONT_H
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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const int m_x;
    int m_fontPixelSize;
    QString m_text;
    QFont m_font;
    int m_contentWidth;
    int m_fontWidth;
    int m_fontHeight;
    int m_angle;
    QColor m_outLineColor;
    QColor m_contentColor;
    QPixmap m_strokeFontPixmap;

private:
    bool drawStrokeFontPixmap();
    QSize minSize(int fontWidth, int fontHeight, qreal angle);
};
#endif // STROKEFONT_H
