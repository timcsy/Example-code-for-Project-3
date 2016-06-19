#ifndef BARRIER_H
#define BARRIER_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BARRIER_DENSITY 20.0f
#define BARRIER_FRICTION 0.5f
#define BARRIER_RESTITUTION 0.5f

class Barrier : public GameItem
{
public:
    Barrier(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
    void contacted();
};

class Wood : public Barrier
{
public:
    Wood(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
};

class Rock : public Barrier
{
public:
    Rock(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
};

class Ice : public Barrier
{
public:
    Ice(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
};

#endif // BARRIER_H
