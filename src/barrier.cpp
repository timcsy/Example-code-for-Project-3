#include "barrier.h"
#include "bird.h"

Barrier::Barrier(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    if(turn) bodydef.angle = 3.1415926/2;
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = BARRIER_DENSITY;
    fixturedef.friction = BARRIER_FRICTION;
    fixturedef.restitution = BARRIER_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Barrier::Contact(b2Vec2 impulse, GameItem *gameItem)
{
    if(impulse.Length()>100)setScore(impulse.Length()*2);
    else isContact = false;
}

void Barrier::contacted()
{
    deleteItem(10);
}

Wood::Wood(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Barrier(x,y,w,h,turn,timer,pixmap,world,scene)
{

}

void Wood::Contact(b2Vec2 impulse, GameItem* gameItem)
{
    if(dynamic_cast<RedBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(2*impulse.Length());}
    else if(dynamic_cast<YellowBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(2*impulse.Length());}
    else if(dynamic_cast<GreenBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(2*impulse.Length());}
    else if(dynamic_cast<BlackBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<BlueBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<WhiteBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else isContact = false;
}

Rock::Rock(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Barrier(x,y,w,h,turn,timer,pixmap,world,scene)
{

}

void Rock::Contact(b2Vec2 impulse, GameItem *gameItem)
{
    if(dynamic_cast<RedBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<YellowBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<GreenBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<BlackBird*>(gameItem) && impulse.Length()>50){setScore(2*impulse.Length());}
    else if(dynamic_cast<BlueBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<WhiteBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else isContact = false;
}

Ice::Ice(float x, float y, float w, float h, bool turn, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Barrier(x,y,w,h,turn,timer,pixmap,world,scene)
{

}

void Ice::Contact(b2Vec2 impulse, GameItem *gameItem)
{
    if(dynamic_cast<RedBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<YellowBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(impulse.Length());}
    else if(dynamic_cast<GreenBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(impulse.Length());}
    else if(dynamic_cast<BlackBird*>(gameItem) && impulse.Length()>50){setScore(impulse.Length());}
    else if(dynamic_cast<BlueBird*>(gameItem) && impulse.Length()>5){remove=1;setScore(impulse.Length());}
    else if(dynamic_cast<WhiteBird*>(gameItem) && impulse.Length()>50){remove=1;setScore(impulse.Length());}
    else isContact = false;
}
