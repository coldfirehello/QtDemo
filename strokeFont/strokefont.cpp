#include "strokefont.h"
#include <QFontMetrics>
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QFontDatabase>

#define PI acos(-1)

StrokeFont::StrokeFont(QWidget *parent): QWidget(parent),
    m_drawXoffset(2),
    m_fontPixelSize(20),
    m_fontWidth(2),
    m_rotateAngle(0),
    m_rotateOffsetLength(0),
    m_outLineColor("#FFA600"),
    m_contentColor("#FFFFFF")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_fontHeight = m_fontPixelSize + m_fontWidth * 2;

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
    m_fontHeight = m_fontPixelSize + m_fontWidth * 2;

    m_font.setPixelSize(m_fontPixelSize);
    m_font.setWeight(m_fontWidth);
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
    m_contentWidth = fontMetrics.width(m_text) + m_drawXoffset * 2;

    QSize size(m_contentWidth, m_fontHeight);

    if(0 != m_rotateAngle)
    {
        size = minSize(m_contentWidth, m_fontHeight, m_rotateAngle);
    }

    setFixedSize(size);

    drawStrokeFontPixmap();
}

bool StrokeFont::drawStrokeFontPixmap()
{
    bool ret = false;

    if(!m_text.isEmpty())
    {
        QPixmap srcPixmap(m_contentWidth, m_fontHeight);
        srcPixmap.fill(Qt::transparent);

        QPainterPath srcPath;
        srcPath.addText(m_drawXoffset, m_fontPixelSize, m_font, m_text);

        QPainter srcpainter(&srcPixmap);

        QPen pen;
        pen.setColor(m_outLineColor);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(m_fontWidth);

        srcpainter.setRenderHint(QPainter::Antialiasing);
        srcpainter.setRenderHint(QPainter::SmoothPixmapTransform);
        srcpainter.strokePath(srcPath, pen);
        srcpainter.fillPath(srcPath, QBrush(m_contentColor));

        QPixmap pixmap(this->size());
        pixmap.fill(Qt::transparent);
        m_strokeFontPixmap = pixmap;

        QPainter painter(&m_strokeFontPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        if(m_rotateAngle > 0)
        {
           painter.translate(m_rotateOffsetLength, 0);
        }
        else
        {
            painter.translate(0, m_rotateOffsetLength);
        }

        painter.rotate(m_rotateAngle);

        QRect rect(0, 0, srcPixmap.width(), srcPixmap.height());
        painter.drawPixmap(rect, srcPixmap);

        ret = true;

        update();
    }

    return ret;
}

/*
 *  L1(0,0)—————————————— +x
           |L1—— —— —— R1
           ||          |
           ||          |
           |L2—— —— —— R2
          +Y

    L1是原点，L1、L2、R1、R2是待旋转矩形4个坐标点
*/

QSize StrokeFont::minSize(int fontWidth, int fontHeight, int angle)
{
    QSize ret;

    double radian = PI * angle / 180;

    if(angle > 0)
    {
        QPoint rotateL1(0, 0);
        QPoint rotateL2(0 * cos(radian) - fontHeight * sin(radian), fontHeight * cos(radian) + 0 * sin(radian));
        QPoint rotateR1(fontWidth * cos(radian) - 0 * sin(radian), 0 * cos(radian) + fontWidth * sin(radian));
        QPoint rotateR2(fontWidth * cos(radian) - fontHeight * sin(radian), fontHeight * cos(radian) + fontWidth * sin(radian));

        ret.setWidth(rotateR1.x() - rotateL2.x() + 1);
        ret.setHeight(rotateR2.y() + 1);

        m_rotateOffsetLength = abs(rotateL2.x()) + 1;
    }
    else
    {
        QPoint rotateL1(0, 0);
        QPoint rotateL2(0 * cos(radian) - fontHeight * sin(radian), fontHeight * cos(radian) + 0 * sin(radian));
        QPoint rotateR1(fontWidth * cos(radian) - 0 * sin(radian), 0 * cos(radian) + fontWidth * sin(radian));
        QPoint rotateR2(fontWidth * cos(radian) - fontHeight * sin(radian), fontHeight * cos(radian) + fontWidth * sin(radian));

        ret.setWidth(rotateR2.x() + 1);
        ret.setHeight(rotateL2.y() - rotateR1.y() + 1);

        m_rotateOffsetLength = abs(rotateR1.y()) + 1;
    }

    return ret;
}
