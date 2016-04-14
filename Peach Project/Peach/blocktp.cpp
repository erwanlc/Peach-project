#include "blocktp.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include <qmath.h>
#include "Game.h"

extern Game * game;

BlockTp::BlockTp(int x, int y, int xx, int yy): QObject(){                    //Ajout 15/11

    setPos(x,y);
    posXdest = xx;
    posYdest = yy;
    setZValue(2);
    texture_tuyau = QPixmap(":/images/tuyau.png");
}
QRectF BlockTp:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void BlockTp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, texture_tuyau);
}

QPainterPath BlockTp::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_SIZE/2-COLLISION_POSX)+0.5, -(COLLISION_SIZE/2-COLLISION_POSY)+0.5, COLLISION_SIZE-1, COLLISION_SIZE-1);
    return path;
}
void BlockTp::playerCollision(QPointF pos)        //ajout fonction de collision avec un "Player"
{
    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;

    if(angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        emit sendPosTp(posXdest,posYdest);


    }
}
void BlockTp::advance(int step)       //modification 21/10 de toute la fonction advance
{
    if (!step) return;
    collision();

}

void BlockTp::collision(){
    colliding_items = collidingItems();                         //On enregistre tous les objets en collisions avec notre objet
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(playerView)){
            playerCollision(collidingItems().at(i)->pos());
            return;
        }
    }
}

QPixmap BlockTp::getTextureBlock(){
    return texture_tuyau;
}

void BlockTp::setTextureBlock(QPixmap newTextureBlock){
    texture_tuyau=newTextureBlock;
}
