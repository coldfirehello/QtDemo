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
    m_outLineColor("#FFA600"),
    m_contentColor("#FFFFFF")
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    QFontDatabase::addApplicationFont("./Alibaba-PuHuiTi-Heavy.ttf");

    m_font.setFamily("Alibaba PuHuiTi Heavy");
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

    setFixedWidth(m_contentWidth + m_x * 2);
    setFixedHeight(m_fontPixelSize * 1.2);

    update();
}

void StrokeFont::setStrokeFont(const QColor& outLineColor, const QColor& fontColor, int fontWidth, int fontPixelSize, const QString& family)
{
    m_outLineColor = outLineColor;
    m_contentColor = fontColor;
    m_fontWidth = fontWidth;
    m_fontPixelSize = fontPixelSize;

    m_font.setPixelSize(m_fontPixelSize);
    m_font.setWeight(m_fontWidth);
    if(!family.isEmpty())
    {
        m_font.setFamily(family);
    }

    QFontMetrics fontMetrics(m_font);
    m_contentWidth = fontMetrics.width(m_text);

    setFixedWidth(m_contentWidth + m_x * 2);
    setFixedHeight(m_fontPixelSize * 1.2);

    update();
}

void StrokeFont::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPainterPath path;
    path.addText(m_x, m_fontPixelSize, m_font, m_text);

    QPen pen;
    pen.setColor(m_outLineColor); //QColor("#FFA600")
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(m_fontWidth);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.strokePath(path, pen);
    painter.fillPath(path, QBrush(m_contentColor));

    QWidget::paintEvent(event);
}
