#include "playerview.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Enemy.h"
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <qpainter.h>
#include <game.h>
#include <math.h>
#include <typeinfo>
#include <QTime>
#include <QCoreApplication>
#include "piece.h"
#include "blocksurprise.h"
#include "blockheart.h"
#include "mushroomheart.h"
#include "blockpower.h"
#include "mushroompower.h"
#include "blockdestructible.h"
#include "blocktp.h"
#include "mario.h"
#include "turtle.h"

extern Game * game;

playerView::playerView(): speedx(0), speedy(-40), gravity(2.5){
    // set graphic
    setPos(90,710);
    texture=this->setPlayerViewRight();
    right=false;
    left=false;
    up=false;
    onGround = true;
    onAirRight=false;
    onAirLeft=false;
    leftPossible=true;
    rightPossible=true;
    dress=false;
    hardFall=false;
    fall=true;
    hit=false;
    blockActivated=false;
    hitTime = 0;
    posCenterOn.setY(0);
    direction = true;
    collisionDownTuyau=false;
    tp=false;
    playerJump = new QMediaPlayer();
    playerJump->setMedia(QUrl("qrc:/sounds/peach03.wav"));
    playerDmg = new QMediaPlayer();
    playerDmg->setMedia(QUrl("qrc:/sounds/peachHit.wav"));
    win = new QMediaPlayer();
    win->setMedia(QUrl("qrc:/sounds/Ouh.. Mamma mia.wav"));
}

void playerView::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        left=true;
        direction=false;
    }
    else if (event->key() == Qt::Key_Right){
        right=true;
        direction=true;
    }

    if (event->key() == Qt::Key_Up){
        if (event->key()==Qt::Key_Left)
        {
            left=true;
        }
        else if (event->key()==Qt::Key_Right)
        {
            right=true;
        }
        up=true;
        onGround=false;
    }
    else if (event->key()==Qt::Key_Down && !onGround){
        dress=true;
    }
    else if (event->key()==Qt::Key_Down){
        if(tp){
            setPos(destinationXTP,destinationYTP);
        }
        tp=false;
    }
    else if (event->key()==Qt::Key_F && Player::power){
        flamme=new Power(direction);
        if(direction) flamme->setPos(x()+200,y()-40);
        if(!direction) flamme->setPos(x()-200,y()-30);
        view->scene()->addItem(flamme);
    }
    else if(event->key()==Qt::Key_R){
        setPos(7000, 570);
        view->centerOn(this);
    }
    if(event->key()==Qt::Key_Space){
        hardFall=true;
    }
}

void playerView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Right)
    {
        right=false;
    }
    else if (event->key()==Qt::Key_Left)
    {
        left=false;
    }
    else if (event->key()==Qt::Key_Up)
    {
        up=false;
    }
    else if(event->key()==Qt::Key_F){
        if(Player::power==true)delete(flamme);
    }
    else if(event->key()==Qt::Key_R){
        right=false;
        left=false;
        up=false;
    }
}

QRectF playerView:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

QPainterPath playerView::shape() const
{
    QPainterPath path;
    path.addRect( -(COLLISION_WIDTH/2-COLLISION_POSX), -(COLLISION_HEIGHT/2-COLLISION_POSY), COLLISION_WIDTH, COLLISION_HEIGHT-14);
    return path;
}


void playerView::isOnGround()
{
    speedy=-40;
    speedx=0;
    onGround=true;
    onAirRight=false;
    onAirLeft=false;
    dress=false;
    hardFall=false;
    fall=false;
}

//Collision with block
void playerView::blockCollision(QPointF pos)
{
    qreal margin = 0.5;

    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;


    if (angleToblock < diagonalAngle && angleToblock >= -diagonalAngle)
    {
        //Collision left
        setX(pos.x()+(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();

    }
    else if (angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        setY(pos.y()+(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        groundTest();
    }
    else if (angleToblock >= diagonalAngle && angleToblock < Pi-diagonalAngle)
    {
        //Collision down
        setY(pos.y()-(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        isOnGround();
    }
    else
    {
        //Collision right
        setX(pos.x()-(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();
    }
}

//Collision with the pipe
void playerView::blockTPCollision(QPointF pos)                    //Ajout 15/11
{
    qreal margin = 0.5;

    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;


    if (angleToblock < diagonalAngle && angleToblock >= -diagonalAngle)
    {
        //Collision left
        setX(pos.x()+(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();
    }
    else if (angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        setY(pos.y()+(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        groundTest();
    }
    else if (angleToblock >= diagonalAngle && angleToblock < Pi-diagonalAngle)
    {
        //Collision down
        setY(pos.y()-(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        collisionDownTuyau=true;
        isOnGround();
    }
    else
    {
        //Collision right
        setX(pos.x()-(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();
    }
}

//Collision with block surprise, mushroom...
void playerView::blockSurpriseCollision(QPointF pos)
{
    qreal margin = 0.5;

    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;


    if (angleToblock < diagonalAngle && angleToblock >= -diagonalAngle)
    {
        //Collision left
        setX(pos.x()+(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();
    }
    else if (angleToblock < -diagonalAngle && angleToblock >= -Pi+diagonalAngle)
    {
        //Collision up
        setY(pos.y()+(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        groundTest();
        blockActivated=true;
    }
    else if (angleToblock >= diagonalAngle && angleToblock < Pi-diagonalAngle)
    {
        //Collision down
        setY(pos.y()-(margin+25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        isOnGround();
    }
    else
    {
        //Collision right
        setX(pos.x()-(margin+40+COLLISION_WIDTH/2)-COLLISION_POSX);
        groundTest();
    }
}

////Collision with ennemies Goomba
void playerView::enemyCollision(QPointF pos)            //ajout 21/10 fonction de collision avec un "Enemy"
{

    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;

    if (angleToblock >= diagonalAngle && angleToblock < Pi-diagonalAngle)       //si collision en bas du joueur
    {
        //Collision down
        //destroy Ennemy
        emit collisionDownWithEnemy();
    }
    else {
        //if right/left/up colliding then lose 1 live
        Player::heart=Player::heart-1;
        Player::power=false;
        this->hit = true;
        this->hitTime = HIT_TIME;
        playerDmg->play();
    }
}

//Collision with ennemies turtle
void playerView::turtleCollision(QPointF pos){
    float Pi=3.14;

    QLineF lineToblock(pos, this->pos()+QPointF(COLLISION_POSX,COLLISION_POSY));
    qreal angleToblock = -acos(lineToblock.dx() / lineToblock.length());
    if (lineToblock.dy() < 0) angleToblock = -angleToblock;

    qreal diagonalAngle = Pi/4;

    if (angleToblock >= diagonalAngle && angleToblock < Pi-diagonalAngle)       //si collision en bas du joueur
    {
        //Collision down
        setY(pos.y()-(25+COLLISION_HEIGHT/2)-COLLISION_POSY);
        isOnGround();
        emit collisionDownWithEnemy();
    }
    else {
        //if right/left/up colliding then lose 1 live
        //qDebug()<<"1 life lose";
        Player::heart=Player::heart-1;
        Player::power=false;
        this->hit = true;
        this->hitTime = HIT_TIME;
        playerDmg->play(); //SOUND
    }
}

void playerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, texture);
    if(hit){
        painter->setBrush(Qt::red);
        painter->setOpacity(0.75);
        painter->drawPath(shape());
    }
}

//Update of the player
void playerView::advance(int step)
{
    if (!step)
        return;
    if (hit)
    {
        if ( (hitTime -= 16.66) <= 0 )
        {
            hit = false;
            this->update(this->boundingRect());
        }
    }

    if(!Player::gameOver){
        deplacement(); //function for moving
        collision(); //function for colliding
        setTexture(); //function to set textures
    }

    view->centerOn(this);

    //If the player fall it loose life
    if(pos().y()>1200)
    {
        Player::heart--;
        Player::power=false;
        playerDmg->play();//SOUND
        setPos(90,710);
    }
}

void playerView::deplacement(){
    if(onGround==false){
        if(up)playerJump->play(); //SOUND
        if (!fall){
            if((!onAirRight && !onAirLeft) || dress){
                if(right && rightPossible){
                    speedx=6;
                    onAirRight=true;
                }
                else if(left && leftPossible)
                {
                    speedx=-6;
                    onAirLeft=true;
                }
                else
                {
                    speedx=0;
                }
            }
            else{
                if (onAirRight && rightPossible)
                {
                    if (onAirLeft)return;
                    else speedx=6;
                }
                else if(onAirLeft && leftPossible)
                {
                    if (onAirRight) return;
                    else speedx=-6;
                }
                else
                {
                    if ((onAirRight && rightPossible) || (onAirLeft && leftPossible)) return;
                    else speedx=0;
                }
            }
        }

        else if(fall){
            if (right && rightPossible)
            {
                speedx=3;
            }
            else if(left && leftPossible)
            {
                speedx=-3;
            }
            else{
                speedx=0;
            }
            speedy=6;
        }
        if(hardFall){
            speedx=0;
            speedy=50;
        }
        if (dress)speedy=speedy+1;
        else speedy=speedy+gravity;
        setPos(mapToParent(speedx, speedy));
        collisionDownTuyau=false;
    }
    else if(onGround==true){
        if (right)
        {
            speedx=20;
            setPos(mapToParent(speedx, 0));
            collisionDownTuyau=false;
        }
        else if (left)
        {
            speedx=-20;
            setPos(mapToParent(speedx, 0));
            collisionDownTuyau=false;
        }
        else{
            speedx=0;
        }
    }
}

void playerView::collision(){
    //collision

    // Ajout de 27/10
    colliding_items = collidingItems();
    //On test si il y a du vide à 25px en dessous de peach. Si oui alors c'est la chute. Si non, on est sur du sol.
    if (colliding_items.size()==0)
    {
        if(onGround){

            groundTest();
        }

        else if(left){
            leftTest();
        }

        else if(right){
            rightTest();
        }
    }

    else{
        for (int i = 0, n = colliding_items.length(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Brique)){
                blockCollision(collidingItems().at(i)->pos());
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(BlockLimit)){
                blockCollision(collidingItems().at(i)->pos());
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(BlockSurprise)){
                blockSurpriseCollision(collidingItems().at(i)->pos());
                if (blockActivated){
                    scene()->addItem(new Piece (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()-64,0));
                    scene()->addItem(new Brique (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()));
                    delete(colliding_items[i]);
                    blockActivated=false;
                }
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(BlockHeart)){
                blockSurpriseCollision(collidingItems().at(i)->pos());
                if (blockActivated){
                    scene()->addItem(new MushroomHeart (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()));
                    scene()->addItem(new Brique (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()));
                    delete(colliding_items[i]);
                    blockActivated=false;
                }
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(BlockPower)){
                blockSurpriseCollision(collidingItems().at(i)->pos());
                if (blockActivated){
                    scene()->addItem(new MushroomPower (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()));
                    scene()->addItem(new Brique (colliding_items[i]->pos().x(), colliding_items[i]->pos().y()));
                    delete(colliding_items[i]);
                    blockActivated=false;
                }
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(BlockDestructible)){
                blockSurpriseCollision(collidingItems().at(i)->pos());
                if (blockActivated){
                    delete(colliding_items[i]);
                    blockActivated=false;
                    collisionDownTuyau=false;
                }
                return;
            }
            else if(typeid(*(colliding_items[i])) == typeid(BlockTp)){                    //Ajout 15/11
                blockTPCollision(collidingItems().at(i)->pos());
            }
            else if(typeid(*(colliding_items[i])) == typeid(Enemy) && hit==false){
                enemyCollision(collidingItems().at(i)->pos());
                i--;
                return;
            }
            else if(typeid(*(colliding_items[i])) == typeid(Turtle) && hit==false){
                turtleCollision(collidingItems().at(i)->pos());
                i--;
                return;
            }
            else if(typeid(*(colliding_items[i])) == typeid(Mario)){
                win->play();
                return;
            }
        }
    }
}

//We test if the player is on ground or not
void playerView::groundTest(){
    setPos(mapToParent(0, 25));

    QList<QGraphicsItem *> colliding_itemsBis = collidingItems();

    if (colliding_itemsBis.size()==0)
    {
        fall =true;
        onGround=false;
        return;
    }
    else{
        setPos(mapToParent(0, -25));
    }
}

//We test if left is free
void playerView::leftTest(){
    setPos(mapToParent(-10, 0));

    QList<QGraphicsItem *> colliding_itemsBis = collidingItems();
    if (colliding_itemsBis.size()<=1)
    {
        leftPossible=true;
        setPos(mapToParent(10, 0));
    }
    else{
        setPos(mapToParent(10, 0));
        leftPossible=false;
        rightPossible=true;
        //qDebug()<<"taille "<<colliding_itemsBis.size();
        //qDebug()<<"lenght"<<colliding_itemsBis.length();
    }
}

//We test if right is free
void playerView::rightTest(){
    setPos(mapToParent(10, 0));

    QList<QGraphicsItem *> colliding_itemsBis = collidingItems();
    if (colliding_itemsBis.size()<=1)
    {
        rightPossible=true;
        setPos(mapToParent(-10, 0));
    }
    else
    {
        setPos(mapToParent(-10, 0));
        rightPossible=false;
        leftPossible=true;
    }
}

//Signal for pipe
void playerView::receiveTPsignal(int x,int y){
    destinationXTP=x;
    destinationYTP=y;
    tp=true;
}

void playerView::setTexture(){
    if(onGround){
        texture = this->setPlayerViewRight();
    }
    if (dress){
        if(right)texture = this->setPlayerViewDress();
        else if(left)texture=this->setPlayerViewLeftDress();
        else texture = this->setPlayerViewRightDress();
    }
    if(Player::power){
        texture = this->setPlayerPeachOnFire();
    }
}


QPixmap playerView::setPlayerViewLeft(){
    return QPixmap(":/images/200px-Peach_FS.png");
}

QPixmap playerView::setPlayerViewLeftDress(){
    return QPixmap(":/images/Peach_dressL.png");
}

QPixmap playerView::setPlayerViewRight(){
    return QPixmap(":/images/200px-Peach_FS.png");
}

QPixmap playerView::setPlayerViewRightDress(){
    return QPixmap(":/images/Peach_dressR.png");
}

QPixmap playerView::setPlayerViewDress(){
    return QPixmap(":/images/Peach_dress.png");
}

QPixmap playerView::setPlayerHit(){
    return QPixmap(":/images/peachHit.png");
}
QPixmap playerView::setPlayerPeachOnFire(){
    return QPixmap(":/images/peachIsOnFire.png");
}
