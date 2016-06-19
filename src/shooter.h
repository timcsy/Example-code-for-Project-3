#ifndef SHOOTER_H
#define SHOOTER_H

#include <gameitem.h>
#include <QGraphicsScene>

class Shooter : public GameItem
{
public:
    Shooter(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

class Rope : public GameItem
{
public:
    Rope(b2Vec2 pb, b2Vec2 ps, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void paint(b2Vec2 pb, b2Vec2 ps);
    void setExtend(b2Vec2 pb, b2Vec2 ps);
    QPixmap picture;
};

#endif // SHOOTER_H
