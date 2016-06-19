#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <mainwindow.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class MainWindow;

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
    void contacted();
    int isOut;
    void isOutOfBound();
    bool ready;
    virtual void feature();
    bool travel;
    MainWindow *callparent;
    QTimer *g_timer;
    QGraphicsScene *g_scene;
};

class RedBird : public Bird
{
public:
    RedBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
};

class YellowBird : public Bird
{
public:
    YellowBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
};

class GreenBird : public Bird
{
public:
    GreenBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
};

class BlackBird : public Bird
{
public:
    BlackBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QList<GameItem*> g_itemList, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
    QList<GameItem*> itemList;
};

class BlueBird : public Bird
{
public:
    BlueBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
};

class WhiteBird : public Bird
{
public:
    WhiteBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void feature();
};

#endif // BIRD_H
