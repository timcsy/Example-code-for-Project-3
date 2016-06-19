#include "shooter.h"

Shooter::Shooter(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSizeF(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    bodyDef.type = b2_staticBody;
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}

Rope::Rope(b2Vec2 pb, b2Vec2 ps, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    float32 w = (ps-pb).Length();
    // Set pixmap
    picture = pixmap;
    g_pixmap.setPixmap(picture.scaled(w*g_windowsize.height()/32,h*g_windowsize.width()/18));
    g_pixmap.setTransformOriginPoint(0,0);
    g_size = QSizeF(w,h);

    // Create body
    b2BodyDef bodyDef;
    g_body = world->CreateBody(&bodyDef);

    scene->addItem(&g_pixmap);
    paint(pb,ps);
}

void Rope::paint(b2Vec2 pb, b2Vec2 ps)
{
    b2Vec2 delta = 0.2/(pb-ps).Length()*(pb-ps);
    b2Vec2 pos = ps+b2Vec2(delta.y,-delta.x);
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y)/g_worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation((((((ps-pb).x/(ps-pb).Length()>=0)?1:-1)*acosf((ps-pb).y/(ps-pb).Length())*180)/3.14159));
}

void Rope::setExtend(b2Vec2 pb, b2Vec2 ps)
{
    float32 h = (ps-pb).Length();
    float32 w = 0.4;
    g_pixmap.setPixmap(picture.scaled(w*g_windowsize.width()/32,h*g_windowsize.height()/18));
    paint(pb,ps);
}
