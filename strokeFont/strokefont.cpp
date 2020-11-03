#include "strokefont.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QImage>

StrokeFont::StrokeFont(QWidget *parent): QWidget(parent),
    m_fontPixelSize(20),
    m_fontWidth(2),
    m_rotateAngle(0),
    m_outLineColor("#FFA600"),
    m_contentColor("#FFFFFF")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_contenHeight = m_fontPixelSize + m_fontWidth * 2;

    m_font.setPixelSize(m_fontPixelSize);
    m_font.setWeight(m_fontWidth);
    m_font.setFamily(this->font().family());
}

StrokeFont::~StrokeFont()
{

}

void StrokeFont::setText(const QString& text)
{
    m_text = text;

    updateStrokeFontPixmap();
}

void StrokeFont::setStrokeFont(const QColor& outLineColor, const QColor& fontColor, int fontWidth, int fontPixelSize, const QString& family)
{
    m_outLineColor = outLineColor;
    m_contentColor = fontColor;
    m_fontWidth = fontWidth;
    m_fontPixelSize = fontPixelSize;
    m_contenHeight = m_fontPixelSize + m_fontWidth * 2;

    m_font.setPixelSize(m_fontPixelSize);
    if(!family.isEmpty())
    {
        m_font.setFamily(family);
    }

    updateStrokeFontPixmap();
}

void StrokeFont::setRotate(int angle)
{
    if(angle > 90)
    {
        angle = 90;
    }
    else if(angle < -90)
    {
        angle = -90;
    }

    m_rotateAngle = angle;

    updateStrokeFontPixmap();
}

QPixmap StrokeFont::strokeFontPixmap()
{
    return m_strokeFontPixmap;
}

void StrokeFont::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if(!m_strokeFontPixmap.isNull())
    {
        painter.drawPixmap(QRect(0, 0, m_strokeFontPixmap.width(), m_strokeFontPixmap.height()), m_strokeFontPixmap);
    }
}

void StrokeFont::updateStrokeFontPixmap()
{
    QFontMetrics fontMetrics(m_font);
    m_contentWidth = fontMetrics.width(m_text) + m_fontWidth * 2;

    drawStrokeFontPixmap();

    setFixedSize(m_strokeFontPixmap.size());
}

bool StrokeFont::drawStrokeFontPixmap()
{
    bool ret = false;

    if(!m_text.isEmpty())
    {
        int maxLength = m_contentWidth > m_contenHeight ? m_contentWidth : m_contenHeight;
        maxLength *= 2;

        int x = (maxLength - m_contentWidth) / 2;
        int y = (maxLength - m_contenHeight) / 2;
        int centerX = maxLength / 2;
        int centerY = centerX;

        QPixmap srcPixmap(maxLength, maxLength);
        {
            srcPixmap.fill(Qt::transparent);

            QPainterPath srcPath;
            srcPath.addText(x, y + m_contenHeight, m_font, m_text);

            QPainter srcpainter(&srcPixmap);

            QPen pen;
            pen.setColor(m_outLineColor);
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(m_fontWidth);

            srcpainter.setRenderHint(QPainter::Antialiasing);
            srcpainter.setRenderHint(QPainter::SmoothPixmapTransform);

            srcpainter.translate(centerX, centerY);
            srcpainter.rotate(m_rotateAngle);
            srcpainter.translate(-centerX, -centerY);

            srcpainter.strokePath(srcPath, pen);
            srcpainter.fillPath(srcPath, QBrush(m_contentColor));

            QImage image =  minSizeStrokenFontImage(srcPixmap.toImage());
            m_strokeFontPixmap = QPixmap::fromImage(image);
        }

        ret = true;

        update();
    }

    return ret;
}

QImage StrokeFont::minSizeStrokenFontImage(const QImage& image)
{
    int x1 = image.width() - 1, x2 = 0, y1 = image.height() - 1, y2 = 0;

    for(int x = 0; x < image.width(); ++x)
    {
        for(int y = 0; y < image.height(); ++y)
        {
            QColor color = image.pixelColor(x, y);

            if(color.red() != 0 || color.green() != 0 || color.blue() != 0)
            {
                if(y1 > y)
                {
                    y1 = y;
                }

                if(y2 < y)
                {
                    y2 = y;
                }

                if(x1 > x)
                {
                    x1 = x;
                }

                if(x2 < x)
                {
                    x2 = x;
                }
            }
        }
    }

    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;

    QImage ret(QSize(width, height), image.format());

    for(int x = x1, i = 0; x <= x2; ++x, ++i)
    {
        for(int y = y1, j = 0; y <= y2; ++y, ++j)
        {
            QColor color = image.pixelColor(x, y);
            ret.setPixelColor(i, j, color);
        }
    }

    ret.save("D:/123.png");

    return ret;
}
