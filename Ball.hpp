#ifndef BALL_HPP
#define BALL_HPP

#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <QColor>
#include "Vector.hpp"

class Ball : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor fillColor READ getFillColor WRITE setFillColor)

public:
    Ball(QQuickItem *parent = 0);

    double getRadius() const;
    void setRadius(const double &radius);

    QColor getBorderColor() const;
    void setBorderColor(const QColor &color);

    QColor getFillColor() const;
    void setFillColor(const QColor &color);

    void paint(QPainter *painter);

    QPointF center() const;

    Vector direction;
    qreal velocity = 0;

private:
    double m_radius = 15;
    QColor m_borderColor = "red";
    QColor m_fillColor = "gray";

signals:
    void radiusChanged();
};

#endif // BALL_HPP
