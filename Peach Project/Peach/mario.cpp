#include "mario.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"

extern Game * game;

Mario::Mario(): QObject(){

    setPos(12200,900);
    setZValue(2);
    textureMario = QPixmap(":/images/mario.png");
}
QRectF Mario:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void Mario::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, textureMario);
}

QPainterPath Mario::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_SIZE/2)+0.5, -(COLLISION_SIZE/2)+0.5, COLLISION_SIZE-1, COLLISION_SIZE-1);//(COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE);
    return path;
}
