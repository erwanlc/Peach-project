#include "Enemy.h"
#include "power.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <math.h>
#include <typeinfo>
#include <QDebug>

extern Game * game;

Enemy::Enemy(int xPos,int yPos,QString penemy,QList <Enemy *>* pgoombaList):speedx(-6){ //ADD DE POS 04/11
    setPos(xPos,yPos); //ADD DE POS 04/11
    enemy=penemy;
    animation=0;
    goombaListGoomba=pgoombaList;
    eView = new EnemyView();
    // drew the rect
    if(enemy=="GOOMBA"){
        texture=eView->getTextureGoombaL(animation);
    }
    else if(enemy=="PIRANHA_PLANTE"){
        texture = eView->setPlantePiranhaViewLeft();
    }
    left=true;
    right=false;
    collisionUpwithPlayer=false;

    //SOUND
    enemyCrushed = new QMediaPlayer();
    enemyCrushed->setMedia(QUrl("qrc:/sounds/peach15.wav"));
}
Enemy::~Enemy(){
    for (int i =0;i<goombaListGoomba->length();i++){
        if(goombaListGoomba->at(i)==this){
            goombaListGoomba->removeAt(i);
        }
    }
}

QRectF Enemy:: boundingRect() const {
    if(enemy=="GOOMBA"){
        return QRectF(-TEXTURE_GOOMBA_WIDTH/2, -TEXTURE_GOOMBA_HEIGHT/2, TEXTURE_GOOMBA_WIDTH, TEXTURE_GOOMBA_HEIGHT);
    }
    else if(enemy=="PIRANHA_PLANTE"){
        return QRectF(-TEXTURE_PIRANHA_WIDTH/2, -TEXTURE_PIRANHA_HEIGHT/2, TEXTURE_PIRANHA_WIDTH, TEXTURE_PIRANHA_HEIGHT);
    }
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(enemy=="GOOMBA"){
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-TEXTURE_GOOMBA_WIDTH/2, -TEXTURE_GOOMBA_HEIGHT/2, texture);
    }
    else if(enemy=="PIRANHA_PLANTE"){
        painter->setBrush(Qt::NoBrush);
        painter->drawPixmap(-TEXTURE_PIRANHA_WIDTH/2, -TEXTURE_PIRANHA_HEIGHT/2, texture);
        texture= eView->setPlantePiranhaViewLeft();
    }
}
QPainterPath Enemy::shape() const
{
    QPainterPath path;
    if(enemy=="GOOMBA"){
    path.addRect(-(COLLISION_GOOMBA_SIZE/2-COLLISION_GOOMBA_POSX)+0.5, -(COLLISION_GOOMBA_SIZE/2-COLLISION_GOOMBA_POSY)+0.5, COLLISION_GOOMBA_SIZE-1, COLLISION_GOOMBA_SIZE-1);//modification 21/10
    }
     else if(enemy=="PIRANHA_PLANTE"){
        path.addRect(-(TEXTURE_PIRANHA_WIDTH/2-COLLISION_GOOMBA_POSX)+0.5, -(TEXTURE_PIRANHA_HEIGHT/2-COLLISION_GOOMBA_POSY)+0.5, TEXTURE_PIRANHA_WIDTH-1, TEXTURE_PIRANHA_HEIGHT-1);//modification 21/10
    }
    return path;
}

void Enemy::playerCollision(QPointF pos)        //ajout fonction de collision avec un "Player"
{
    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_GOOMBA_POSX,COLLISION_GOOMBA_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;

    if(angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        //destroy Ennemy
        //qDebug()<<"CollisionUpWithPlayer = "<<collisionUpwithPlayer;
        if(collisionUpwithPlayer){
            enemyCrushed->play(); //SOUND
            delete(this);
        }
        else{
            //qDebug()<<"CollisionUpWithPlayer but prob!!";
        }

    }
}

void Enemy::advance(int step)       //modification 21/10 de toute la fonction advance
{
    if (!step) return;

    animation++;
    if(animation>=5)animation=0;
    if(enemy=="GOOMBA"){
        deplacement();
        collision();
        if(speedx<0)texture=eView->getTextureGoombaL(animation);
        else texture=eView->getTextureGoombaR(animation);
     }
    else if(enemy=="PIRANHA_PLANTE"){
        collision();
    }
}

void Enemy::deplacement(){
    setPos(mapToParent(speedx,0));
}
void Enemy::collision(){
    colliding_items = collidingItems();                         //On enregistre tous les objets en collisions avec notre objet
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
            //qDebug()<<"Collision avec flammes";
        }
    }
}

void Enemy::playerCollisionUp(){
    collisionUpwithPlayer=true;
    //qDebug()<<"CollisionUpWithPlayer function = "<<collisionUpwithPlayer;
}

void Enemy::piranhaAttack(){

}
