#include "AppController.hpp"

AppController::AppController(QObject *parent) : QObject(parent), updateTimer(this), eng(_rd())
{
    // Init engine
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    rootObj = engine.rootObjects().at(0);
    window = qobject_cast<QQuickWindow*>(rootObj);
    if(!window)
    {
        qFatal("Error: Your root item has to be a window.");
        exit(-1);
    }

    window->show();
    rootItem = window->contentItem();
    container = rootItem->childItems().at(0);

    // Connect signals with slots
    timeScaleSlider = rootObj->findChild<QObject*>("timeScale");
    if(timeScaleSlider == nullptr)
        qCritical() << "timeScaleSlider is null";
    connect(timeScaleSlider, SIGNAL(setTimeScale(double)), this, SLOT(SetTimeScale(double)));

    connect(rootObj, SIGNAL(addBall()), this, SLOT(AddBall()));
    connect(rootObj, SIGNAL(removeBall()), this, SLOT(RemoveBall()));

    // Init timers
    connect(&updateTimer, &QTimer::timeout, this, &Update);
    updateTimer.start(5);

    // Create balls
    for(int i = 0; i < 3; i++)
        AddBall();
}

AppController::~AppController()
{
    for(auto i = 0; i < balls.size(); i++)
        delete balls[i];
}

void AppController::AddBall()
{
    // Rand`s ranges
    std::uniform_int_distribution<> radius_rnd(10, 75);
    std::uniform_int_distribution<> _p_w_rnd(25, container->width() - 125);
    std::uniform_int_distribution<> _p_h_rnd(25, container->height() - 125);
    std::uniform_int_distribution<> _velocity_rnd(100, 200);
    std::uniform_int_distribution<> _color_rnd(0, 255);

    // Find best position with minimum collisions
    qreal radius = radius_rnd(eng);
    QPointF position(0, 0);
    int min_collisions = -1;
    for(auto it = 0; it < 25; it++)
    {
        QPointF pos = QPointF(_p_w_rnd(eng), _p_h_rnd(eng));
        int collisions = 0;

        for(auto i = 0; i < balls.size(); i++)
        {
            Vector delta((pos + QPointF(radius, radius)) - balls[i]->center());
            if(delta.GetLength() <= (radius + balls[i]->getRadius()))
                collisions++;
        }

        if(min_collisions == -1 || collisions < min_collisions)
        {
            position = pos;
            min_collisions = collisions;

            if(collisions == 0)
                break;
        }
    }

    // Create instance
    Ball* ball = new Ball();
    ball->setPosition(position);
    ball->setRadius(radius);
    ball->setBorderColor(QColor("black"));
    ball->setFillColor(QColor(_color_rnd(eng), _color_rnd(eng), _color_rnd(eng)));

    // Set direction and velocity
    ball->direction = Vector(container->width() / 2., container->height() / 2.) - ball->position();
    ball->direction.Normalize();
    ball->velocity = _velocity_rnd(eng);

    // Setup object in qml
    auto ballObj = qobject_cast<QQuickItem*>(ball);
    QQmlEngine::setObjectOwnership(ballObj, QQmlEngine::CppOwnership);
    ballObj->setParentItem(container);
    ballObj->setParent(&engine);

    // Add to array
    balls.append(ball);
}

void AppController::RemoveBall()
{
    if(balls.size() == 0)
        return;

    auto ball = balls.first();
    ball->deleteLater();
    delete ball;
    balls.removeFirst();
}

void AppController::SetTimeScale(qreal scale)
{
    timeScale = scale;
}

void AppController::Update()
{
    if(timeScale == 0)
        return;

    for(auto i = 0; i < balls.size(); i++)
    {
        auto _ball = balls[i];
        if(_ball == nullptr)
            continue;

        // Update positions
        QPointF newPos = _ball->position();
        newPos += QPointF(_ball->direction.x * _ball->velocity * (updateTimer.interval()/1000.) * timeScale,
                          _ball->direction.y * _ball->velocity * (updateTimer.interval()/1000.) * timeScale);

        // Collision with container
        if(newPos.x() <= 0)
        {
            newPos.setX(1);
            _ball->direction.x *= -1;
        }

        if(newPos.y() <= 0)
        {
            newPos.setY(1);
            _ball->direction.y *= -1;
        }

        if(newPos.x() + _ball->getRadius() * 2 >= container->width())
        {
            newPos.setX(container->width() - _ball->getRadius() * 2 - 1);
            _ball->direction.x *= -1;
        }

        if(newPos.y() + _ball->getRadius() * 2 >= container->height())
        {
            newPos.setY(container->height() - _ball->getRadius() * 2 - 1);
            _ball->direction.y *= -1;
        }

        // Collision with other balls
        for(auto j = i+1; j < balls.size(); j++)
        {
            auto _ball_other = balls[j];
            if(_ball_other == nullptr || _ball == _ball_other)
                continue;

            // Calculate distance between balls
            Vector delta(_ball_other->center() - _ball->center());
            qreal r_sum = _ball->getRadius() + _ball_other->getRadius();

            if(delta.GetLength() <= r_sum)
            {
                qreal offset = (r_sum - delta.GetLength()) / 2.;
                delta.Normalize();

                // Change directions
                _ball->direction = delta * -1;
                _ball_other->direction = delta;

                // Correcting positions
                Vector _ball_pos = (delta * -1 * offset) + 0.5;
                _ball->setPosition(_ball->position() - _ball_pos.ToPoint());

                Vector _ball_other_pos = (delta * 1 * offset) - 0.5;
                _ball_other->setPosition(_ball_other->position() + _ball_other_pos.ToPoint());
            }
        }

        // Apply new position
        balls[i]->setPosition(newPos);
    }
}
