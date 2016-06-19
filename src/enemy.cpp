#include "enemy.h"

Enemy::Enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = ENEMY_DENSITY;
    fixturedef.friction = ENEMY_FRICTION;
    fixturedef.restitution = ENEMY_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);

    callparent = dynamic_cast<MainWindow*>(_callparent);
}

void Enemy::Contact(b2Vec2 impulse, GameItem *gameItem)
{
    if(impulse.Length()>30)
    {
        remove=1;
        setScore(5000);
    }
    else
    {
        isContact = 0;
    }
}

void Enemy::contacted()
{
    deleteItem(12);
    if(next_item)
    {
        next_item = 0;
        emit dieSignal();
    }
}
