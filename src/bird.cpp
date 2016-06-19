#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
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
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    ready = false;
    travel = false;
    isOut = 0;

    // Bound timer
    g_timer = timer;
    connect(g_timer, SIGNAL(timeout()), this,SLOT(paint()));

    g_scene = scene;
    g_scene->addItem(&g_pixmap);

    callparent = dynamic_cast<MainWindow*>(_callparent);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::Contact(b2Vec2 impulse, GameItem *gameItem)
{
    if(impulse.Length()>0)
    {
        remove=1;
        travel=false;
        isOut = 2;
        setScore(impulse.Length());
    }
    else
    {
        isContact = false;
    }
}

void Bird::contacted()
{
    isOutOfBound();
    deleteItem(60);
    nextItem();
}

void Bird::isOutOfBound()
{
    if(g_body->IsActive())
    {
        if(isOut == 0 && (g_body->GetPosition().x > g_worldsize.width() || g_body->GetPosition().x < 0)) isOut = 1;
        if(isOut == 0 && (g_body->GetPosition().y > g_worldsize.height() || g_body->GetPosition().y < 0)) isOut = 1;
        if(isOut == 1 && !isDeleted)
        {
            remove = 1;
            travel=false;
            isOut = 2;
        }
    }
}

void Bird::feature()
{

}

RedBird::RedBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene)
{

}

void RedBird::feature()
{

}

YellowBird::YellowBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene)
{

}

void YellowBird::feature()
{
    g_body->SetLinearVelocity(3*g_body->GetLinearVelocity());
}

GreenBird::GreenBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene)
{

}

void GreenBird::feature()
{
    g_body->ApplyForceToCenter(b2Vec2(-20000,0),true);
    g_body->ApplyTorque(-10000,true);
}

BlackBird::BlackBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QList<GameItem*> g_itemList, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene),itemList(g_itemList)
{

}

void BlackBird::feature()
{
    for(int i = 0; i < itemList.size(); i++)
    {
        b2Vec2 r = itemList[i]->g_body->GetPosition() - g_body->GetPosition();
        if(dynamic_cast<Enemy*>(itemList[i]))
        {
            itemList[i]->g_body->ApplyForceToCenter(30/r.Length()*r,true);
        }
        else
        {
            if(r.Length()<5)itemList[i]->g_body->ApplyForceToCenter(10000/r.Length()*r,true);
        }
    }
}

BlueBird::BlueBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene)
{

}

void BlueBird::feature()
{
    b2Vec2 p = g_body->GetPosition();
    b2Vec2 v = g_body->GetLinearVelocity();
    Bird *bird2 = new Bird(p.x,p.y,0.4,g_timer,QPixmap(":/image/blue_bird.png").scaled(g_windowsize.width()/32.0*0.8,g_windowsize.height()/18.0*0.8),callparent,g_world,g_scene);
    callparent->bornBird(bird2,v+b2Vec2(0,2));
    Bird *bird3 = new Bird(p.x,p.y,0.4,g_timer,QPixmap(":/image/blue_bird.png").scaled(g_windowsize.width()/32.0*0.8,g_windowsize.height()/18.0*0.8),callparent,g_world,g_scene);
    callparent->bornBird(bird3,v+b2Vec2(0,-2));
}

WhiteBird::WhiteBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, QWidget *_callparent, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,_callparent,world,scene)
{

}

void WhiteBird::feature()
{
    b2Vec2 p = g_body->GetPosition();
    Bird *egg = new Bird(p.x,p.y-0.51,0.5,g_timer,QPixmap(":/image/egg.png").scaled(g_windowsize.width()/32.0*0.6,g_windowsize.height()/18.0*0.8),callparent,g_world,g_scene);
    callparent->bornBird(egg,b2Vec2(0,-10));
}
