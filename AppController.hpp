#ifndef APPCONTROLLER_HPP
#define APPCONTROLLER_HPP

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include <random>

#include "Vector.hpp"
#include "Ball.hpp"

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = 0);
    ~AppController();

private:
    QQmlApplicationEngine engine;
    QQuickWindow *window;
    QQuickItem *rootItem;
    QQuickItem *container;
    QObject *rootObj;
    QObject *timeScaleSlider;

    QTimer updateTimer;

    QVector<Ball*> balls;
    qreal timeScale = 1.0;

    std::random_device _rd;
    std::mt19937 eng;

signals:

public slots:
    void AddBall();
    void RemoveBall();

    void SetTimeScale(qreal scale);
    void Update();
};

#endif // APPCONTROLLER_HPP
