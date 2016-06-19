#include "gameitem.h"

GameItem::GameItem(b2World *world):
    g_body(NULL),g_world(world),remove(0),next_item(false),isContact(false),scored(false),isDeleted(false)
{
}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::deleteItem(int time)
{
    if(!isDeleted && remove == time + 1)
    {
        remove=0;
        next_item=1;
        g_world->DestroyBody(g_body);
        g_pixmap.setPixmap(QPixmap());
        isDeleted = true;
    }
    else if(remove != 0) remove++;
}

void GameItem::isOutOfBound()
{

}

void GameItem::nextItem()
{
    if(next_item)
    {
        next_item = 0;
        emit nextItemSignal();
    }
}

void GameItem::setScore(int score)
{
    if(!scored)
    {
        //scored = true;
        emit scoreSignal(score);
    }
}

void GameItem::paint()
{
    b2Vec2 pos = g_body->GetPosition();
    //std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
    contacted();
}

b2Vec2 pix2box(QPointF p)
{
    return b2Vec2(p.x()*GameItem::g_worldsize.width()/GameItem::g_windowsize.width(),(1.0f-p.y()/GameItem::g_windowsize.height())*GameItem::g_worldsize.height());
}

QPointF box2pix(b2Vec2 b)
{
    QPointF mappedPoint;
    mappedPoint.setX((b.x* GameItem::g_windowsize.width())/GameItem::g_worldsize.width());
    mappedPoint.setY((1.0f - b.y/GameItem::g_worldsize.height()) * GameItem::g_windowsize.height());
    return mappedPoint;
}
