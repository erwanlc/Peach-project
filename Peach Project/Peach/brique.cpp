#include "brique.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"

extern Game * game;

Brique::Brique(int x, int y): QObject(){

    setPos(x,y);
    setZValue(2);
    texture_block = QPixmap(":/images/Block_marron.png");
}
QRectF Brique:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void Brique::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, texture_block);
}

QPainterPath Brique::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_SIZE/2-COLLISION_POSX)+0.5, -(COLLISION_SIZE/2-COLLISION_POSY)+0.5, COLLISION_SIZE-1, COLLISION_SIZE-1);//(COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE);
    return path;
}

QPixmap Brique::getTextureBlock(){
    return texture_block;
}

void Brique::setTextureBlock(QPixmap newTextureBlock){
    texture_block=newTextureBlock;
}
