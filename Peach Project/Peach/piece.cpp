#include "piece.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include "Game.h"
#include <QDebug>
#include <QTimer>

extern Game * game;

Piece::Piece(int x, int y, QList <Piece*>* pPieceList, QGraphicsItem *parent): QObject(){

    setPos(x,y);
    textureCoin = QPixmap(":/images/coin.png");
    pieceListPiece=pPieceList;

    //SOUND
    coinCatch = new QMediaPlayer();
    coinCatch->setMedia(QUrl("qrc:/sounds/Coin.wav"));

}
Piece::~Piece(){
    for (int i =0;i<pieceListPiece->length();i++){
        if(pieceListPiece->at(i)==this){
            pieceListPiece->removeAt(i);
        }
    }
}
QRectF Piece:: boundingRect() const {return QRectF(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, TEXTURE_WIDTH, TEXTURE_HEIGHT);}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->drawPixmap(-TEXTURE_WIDTH/2, -TEXTURE_HEIGHT/2, textureCoin);
}

QPainterPath Piece::shape() const
{
    QPainterPath path;
    path.addRect(-(COLLISION_SIZE/2-COLLISION_POSX)+0.5, -(COLLISION_SIZE/2-COLLISION_POSY)+0.5, COLLISION_SIZE-1, COLLISION_SIZE-1);//(COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE,COLLISION_SIZE);
    return path;
}

void Piece::advance(int step)
{
    if (!step) return;

    colliding_items = collidingItems();                         //On enregistre tous les objets en collisions avec notre objet
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(playerView)){
            Player::nbCoin=Player::nbCoin+1;
            coinCatch->play();//SOUND
            delete(this);
            return;
        }
    }
}
