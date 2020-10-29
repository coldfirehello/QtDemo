#include "strokefont.h"
#include <QFontMetrics>
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QFontDatabase>

StrokeFont::StrokeFont(QWidget *parent): QWidget(parent),
    m_x(2),
    m_fontPixelSize(20),
    m_fontWidth(2),
    m_angle(57),
    m_outLineColor("#FFA600"),
    m_contentColor("#FFFFFF")
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
//    setAttribute(Qt::WA_TranslucentBackground, true);

    m_fontHeight = m_fontPixelSize + m_fontWidth * 2;

    m_font.setPixelSize(m_fontPixelSize);
    m_font.setWeight(m_fontWidth);
    m_font.setFamily(this->font().family());

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(6);
    this->setGraphicsEffect(shadowEffect);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor(0,0,0,255*0.26));
}

StrokeFont::~StrokeFont()
{

}

void StrokeFont::setText(const QString& text)
{
    m_text = text;

    QFontMetrics fontMetrics(m_font);
    m_contentWidth = fontMetrics.width(m_text);


    QSize size(m_contentWidth, m_fontHeight);

    if(0 != m_angle)
    {
        size = minSize(m_contentWidth, m_fontHeight, m_angle);
    }

    size.setWidth(size.width() + m_x * 2);

    setFixedWidth(m_contentWidth + m_x * 2);
    setFixedHeight(m_fontHeight);
    setFixedSize(size);

    drawStrokeFontPixmap();
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

    QFontMetrics fontMetrics(m_font);
    m_contentWidth = fontMetrics.width(m_text);
    int height = fontMetrics.height();

//    setFixedWidth(m_contentWidth + m_x * 2);
//    setFixedHeight(m_fontHeight);
    QSize size(m_contentWidth, m_fontHeight);

    if(0 != m_angle)
    {
        size = minSize(m_contentWidth, m_fontHeight, m_angle);
    }

    size.setWidth(size.width() + m_x * 2);

//    setFixedWidth(m_contentWidth + m_x * 2);
//    setFixedHeight(m_fontHeight);
    setFixedSize(size);

    drawStrokeFontPixmap();
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

bool StrokeFont::drawStrokeFontPixmap()
{
    bool ret = false;

    if(!m_text.isEmpty())
    {
//        QPixmap pixmap(this->size());
//        pixmap.fill(Qt::transparent);
//        m_strokeFontPixmap = pixmap;

//        QPainter painter(&m_strokeFontPixmap);

//        int x = m_x + (width() - m_contentWidth) / 2;
//        int y = m_fontPixelSize + (height() - m_fontHeight) / 2;

//        QPainterPath path;
//        path.addText(x, y, m_font, m_text);

//        QPen pen;
//        pen.setColor(m_outLineColor);
//        pen.setStyle(Qt::SolidLine);
//        pen.setWidth(m_fontWidth);

//        int centerX = width() / 2;
//        int centerY = height() / 2;

//        painter.translate(centerX, centerY);
//        painter.rotate(m_angle);
//        painter.translate(-centerX, -centerY);

//        painter.setRenderHint(QPainter::Antialiasing);
//        painter.strokePath(path, pen);
//        painter.fillPath(path, QBrush(m_contentColor));

        QPixmap srcPixmap(m_contentWidth + m_x * 2, m_fontHeight);
        srcPixmap.fill(Qt::transparent);

        QPainterPath srcPath;
        srcPath.addText(m_x, m_fontPixelSize, m_font, m_text);

        QPainter srcpainter(&srcPixmap);

        QPen pen;
        pen.setColor(m_outLineColor);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(m_fontWidth);

        srcpainter.setRenderHint(QPainter::Antialiasing);
        srcpainter.strokePath(srcPath, pen);
        srcpainter.fillPath(srcPath, QBrush(m_contentColor));

        QPixmap pixmap(this->size());
        pixmap.fill(Qt::transparent);
        m_strokeFontPixmap = pixmap;

        int centerX = width() / 2;
        int centerY = height() / 2;
        QPainter painter(&m_strokeFontPixmap);
        painter.translate(centerX, centerY);
        painter.rotate(m_angle);
        painter.translate(-centerX, -centerY);

        QRect rect((width() - (m_contentWidth + m_x * 2))/2, (height() - m_fontHeight)/2, (m_contentWidth + m_x * 2), m_fontHeight);
        painter.drawPixmap(rect, srcPixmap);

        ret = true;

        update();
    }

    return ret;
}

QSize StrokeFont::minSize(int fontWidth, int fontHeight, qreal angle)
{
    QSize ret;

    double diagonalLength = sqrt(fontWidth * fontWidth + fontHeight * fontHeight) + 1;

    ret.setWidth(diagonalLength);
    ret.setHeight(diagonalLength);

    return ret;
}
