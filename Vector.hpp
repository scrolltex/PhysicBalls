#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <QtMath>

struct Vector
{
    Vector(qreal x, qreal y)
    {
        this->x = x;
        this->y = y;
    }

    Vector(QPointF point)
    {
        this->x = point.x();
        this->y = point.y();
    }

    Vector()
    {
        this->x = 0;
        this->y = 0;
    }

    qreal GetLength() const
    {
        return qSqrt(qPow(x, 2) + qPow(y, 2));
    }

    Vector GetNormalized() const
    {
        Vector ret(x, y);
        ret.Normalize();
        return ret;
    }

    void Normalize()
    {
        auto vec_l = GetLength();
        x /= vec_l;
        y /= vec_l;
    }

    void FromPoint(QPointF point)
    {
        this->x = point.x();
        this->y = point.y();
    }

    QPointF ToPoint() const
    {
        return QPointF(x, y);
    }

    // Math with qreal
    Vector operator+(const qreal &n)
    {
        return Vector(this->x + n, this->y + n);
    }

    Vector operator-(const qreal &n)
    {
        return Vector(this->x - n, this->y - n);
    }

    Vector operator*(const qreal &n)
    {
        return Vector(this->x * n, this->y * n);
    }

    Vector operator/(const qreal &n)
    {
        return Vector(this->x / n, this->y / n);
    }

    // Math with other Vector
    Vector operator+(const Vector &n)
    {
        return Vector(this->x + n.x, this->y + n.y);
    }

    Vector operator-(const Vector &n)
    {
        return Vector(this->x - n.x, this->y - n.y);
    }

    Vector operator*(const Vector &n)
    {
        return Vector(this->x * n.x, this->y * n.y);
    }

    Vector operator/(const Vector &n)
    {
        return Vector(this->x / n.x, this->y / n.y);
    }

    // Compare with Vector
    bool operator==(const Vector &n)
    {
        return x == n.x && y == n.y;
    }

    bool operator!=(const Vector &n)
    {
        return x == n.x && y == n.y;
    }

    bool operator<(const Vector &n)
    {
        return x < n.x && y < n.y;
    }

    bool operator<=(const Vector &n)
    {
        return !(x > n.x && y > n.y);
    }

    bool operator>(const Vector &n)
    {
        return x > n.x && y > n.y;
    }

    bool operator>=(const Vector &n)
    {
        return !(x < n.x && y < n.y);
    }

    // Vars
    qreal x = 0;
    qreal y = 0;
};

#endif // VECTOR_HPP
