#include "Ball.hpp"

Ball::Ball(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}

double Ball::getRadius() const
{
    return m_radius;
}

void Ball::setRadius(const double &radius)
{
    m_radius = radius;
    setWidth(radius * 2 + 8);
    setHeight(radius * 2 + 8);
}

QColor Ball::getBorderColor() const
{
    return m_borderColor;
}

void Ball::setBorderColor(const QColor &color)
{
    m_borderColor = color;
}

QColor Ball::getFillColor() const
{
    return m_fillColor;
}

void Ball::setFillColor(const QColor &color)
{
    m_fillColor = color;
}

QPointF Ball::center() const
{
    return position() + QPointF(m_radius, m_radius);
}

void Ball::paint(QPainter *painter)
{
    painter->setPen(QPen(m_borderColor, 2));
    painter->setBrush(QBrush(m_fillColor));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(4, 4, m_radius * 2, m_radius * 2);
}
