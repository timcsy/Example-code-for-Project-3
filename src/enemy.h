#ifndef ENEMY_H
#define ENEMY_H

#include <gameitem.h>
#include <mainwindow.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define ENEMY_DENSITY 10.0f
#define ENEMY_FRICTION 0.2f
#define ENEMY_RESTITUTION 0.5f

class MainWindow;

class Enemy : public GameItem
{
public:
    Enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene);
    void Contact(b2Vec2 impulse, GameItem* gameItem);
    void contacted();
    MainWindow *callparent;
};

#endif // ENEMY_H
