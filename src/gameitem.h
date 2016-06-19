#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include <QWidget>

class GameItem : public QWidget
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    friend b2Vec2 pix2box(QPointF  p);
    friend QPointF box2pix(b2Vec2  b);
    bool isContact;
    virtual void Contact(b2Vec2 impulse, GameItem* gameItem){} // call when collided
    virtual void contacted(){} //call when the world unlocked
    int remove;
    bool isDeleted;
    void deleteItem(int time);
    virtual void isOutOfBound();
    int next_item;
    void nextItem();
    bool scored;
    virtual void setScore(int score);

public slots:
    void paint();
    // TODO virtual void collide();
signals:
    void nextItemSignal();
    void dieSignal();
    void scoreSignal(int score);

protected:
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

b2Vec2 pix2box(QPointF  p);
QPointF box2pix(b2Vec2  b);

#endif // GAMEITEM_H
