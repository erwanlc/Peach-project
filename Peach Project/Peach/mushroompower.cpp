#include "mushroompower.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include "Game.h"
#include <QDebug>
#include <QTimer>

extern Game * game;

MushroomPower::MushroomPower(int x, int y, QGraphicsItem *parent): QObject(), QGraphicsItem(parent)
{
    posY=y;
    posYEnd=y-TEXTURE_HEIGHT;

    setPos(x,y);
    textureMushroomPower = QPixmap(":/images/upR.png");
    setZValue(1);
}

QRectF MushroomPower::boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void MushroomPower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, textureMushroomPower);
}

QPainterPath MushroomPower::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_SIZE/2)+0.5, -(COLLISION_SIZE/2)+0.5, COLLISION_SIZE-1, COLLISION_SIZE-1);//(COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE);
    return path;
}

void MushroomPower::advance(int step)
{
    if (!step) return;

    if(posY > posYEnd)
    {
        posY-=3;
        setY(posY);
    }

    colliding_items = collidingItems();                         //On enregistre tous les objets en collisions avec notre objet
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(playerView)){
            Player::power=true;
            delete(this);
            return;
        }
    }
}
