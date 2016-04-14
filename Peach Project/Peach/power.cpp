#include "power.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include <QDebug>
#include <QTimer>

#include "Game.h"
#include "enemy.h"

extern Game * game;

Power::Power(bool dir){
    direction = dir;
    setTexture();

    powerRelease = new QMediaPlayer();
    powerRelease->setMedia(QUrl("qrc:/sounds/Lightning.wav"));
    powerRelease->play();
}
QRectF Power:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void Power::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    //painter->drawPath(shape());
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, texturePower);
    setTexture();
}

QPainterPath Power::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_WIDTH/2-COLLISION_POSX)+0.5, -(COLLISION_HEIGHT/2-COLLISION_POSY)+0.5, COLLISION_WIDTH-1, COLLISION_HEIGHT-1);
    return path;
}

void Power::advance(int step)
{
    if (!step) return;

}

void Power::setTexture(){


    if(direction){
        texturePower=QPixmap(":/images/flammeR.png");
    }

    else if(!direction){
        texturePower = QPixmap(":/images/flammeL.png");
    }
}
