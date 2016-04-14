#include "turtle.h"
#include "power.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <math.h>
#include <typeinfo>
#include <QDebug>

extern Game * game;

Turtle::Turtle(int xPos,int yPos):speedx(-6){
    setPos(xPos,yPos);
    animation=0;
    tView = new TurtleView();

    textureTurtle=tView->getTextureTurtleL(animation);

    left=true;
    right=false;
    collisionUpwithPlayer=false;

    hit=false;
    hitTime = 0;

    turtleCrushed = new QMediaPlayer();
    turtleCrushed->setMedia(QUrl("qrc:/sounds/peach15.wav"));
}

QRectF Turtle:: boundingRect() const {return QRectF(-TEXTURE_TURTLE_WIDTH/2, -TEXTURE_TURTLE_HEIGHT/2, TEXTURE_TURTLE_WIDTH, TEXTURE_TURTLE_HEIGHT);    }

void Turtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_TURTLE_WIDTH/2, -TEXTURE_TURTLE_HEIGHT/2, textureTurtle);
}

QPainterPath Turtle::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_TURTLE_SIZE/2)+0.5, -(COLLISION_TURTLE_SIZE/2)+0.5, COLLISION_TURTLE_SIZE-1, COLLISION_TURTLE_SIZE-1);//modification 21/10
    return path;
}

void Turtle::playerCollision(QPointF pos)        //ajout fonction de collision avec un "Player"
{
    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(0,0));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;

    if(angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        if(collisionUpwithPlayer && !hit){
            turtleCrushed->play();
            if(shell)shell=false;
            else shell=true;
            this->hit = true;
            this->hitTime = HIT_TIME;
        }
    }
}

void Turtle::advance(int step)
{
    if (!step) return;
    if (hit)
    {
        if ( (hitTime -= 16.66) <= 0 )
        {
            hit = false;
            this->update(this->boundingRect());
        }
    }
    animation++;
    if(animation>=5)animation=0;

    if (!shell){
        deplacement();
        if(speedx<0)textureTurtle=tView->getTextureTurtleL(animation);
        else textureTurtle=tView->getTextureTurtleR(animation);
    }else if(speedx<0){
        textureTurtle=tView->getTextureShellL();
    }else{
        textureTurtle=tView->getTextureShellR();
    }
    collision();

}

void Turtle::deplacement(){
    setPos(mapToParent(speedx,0));
}
void Turtle::collision(){
    colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(playerView)){
            playerCollision(collidingItems().at(i)->pos());
            speedx=-speedx;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Brique)){
            speedx=-speedx;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Power)){
            delete(this);
        }
    }
}

void Turtle::playerCollisionUp(){
    collisionUpwithPlayer=true;
}

