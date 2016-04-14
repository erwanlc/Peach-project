#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include "brique.h"
#include <QBrush>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "power.h"
#include "hud.h"
#include "blocksurprise.h"
#include "blockheart.h"
#include "blockpower.h"
#include "blockdestructible.h"
#include "mario.h"
#include "turtle.h"

Game::Game(QGraphicsScene* pscene){

    scene=pscene;

    setView(scene);

    filename=":/decors/Decor1.txt";//Ajout 15/11

    Hud *hud = new Hud(this,Player::heart, Player::nbCoin);
    scene->addItem(hud);

    Mario * mario = new Mario();
    scene->addItem(mario);
    setPlayer();

    setBlock();

    setEnemy();

    tp1=new BlockTp (7488,950,9500,800);                    //Ajout 15/11
    scene->addItem(tp1);                                    //Ajout 15/11
    tp2=new BlockTp (9500,950,7488,800);                    //Ajout 15/11
    scene->addItem(tp2);

    turtle = new Turtle(6000,950);
    scene->addItem(turtle);

    setConnect();
}

//Define the window of the game
void Game::setView(QGraphicsScene *pscene){
    scene=pscene;
    view.setScene(scene);

    //Scene settings
    view.scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
    view.resize(Screen_sizeX+3, Screen_sizeY+3);

    //View settings
    view.setRenderHint(QPainter::Antialiasing);
    view.scene()->setBackgroundBrush(QBrush(QImage(":/images/clouds.jpg")));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::NoDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Super Peach Bros"));
    view.QAbstractScrollArea::setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.QAbstractScrollArea::setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}

//Add the player and defne the focus
void Game::setPlayer(){

    // create the player
    player = new Player(&view);
    // add the item to the scene
    scene->addItem(&player->pView);

    player->pView.setFlag(QGraphicsItem::ItemIsFocusable);
    player->pView.setFocus();
    // add the player to the scene
}

//Add the ennemy Pyranha
void Game::setEnemy(){
    //int numx=0;
    for(int i=0; i < Number_Of_PIRANHA_PLANTE;i++){
        //numx=i*200+710;
        PIRANHA_PLANTE[i]=new Enemy(400,660,"PIRANHA_PLANTE",0);
        scene->addItem(PIRANHA_PLANTE[i]);
        qDebug()<<"PIRANHA PLANTE!";
    }
}

//Read the level file and add the items
void Game::setBlock(){
    qDebug()<<"start creation Block";
    QString filename=":/decors/Decor1.txt";
    QFile fichierDecor(filename);
    if(filename == ":/decors/Decor1.txt"){                    //Ajout 15/11
        decor_nb_BlockX=Decor1_nb_BlockX;                    //Ajout 15/11
        decor_nb_BlockY=Decor1_nb_BlockY;                    //Ajout 15/11
    }

    fichierDecor.open(QIODevice::ReadOnly | QIODevice::Text);

    qDebug()<<"fichier open";
    QTextStream flux(&fichierDecor);
    QString bit = flux.readAll();
    int i=0;
    int x=0;
    int y=0;
    bool endFile=false;
    while(endFile==false){
        if(bit[i]==BLOCK_MARRON){
            scene->addItem(new Brique       (x*64, y*64));
        }
        if(bit[i]==BLOCK_LIMIT){
            scene->addItem(new BlockLimit       (x*64, y*64));
        }
        if(bit[i]==BLOCK_SURPRISE){
            scene->addItem(new BlockSurprise       (x*64, y*64));
        }
        if(bit[i]==BLOCK_HEART){
            scene->addItem(new BlockHeart       (x*64, y*64));
        }
        if(bit[i]==BLOCK_DESTRUCTIBLE){
            scene->addItem(new BlockDestructible       (x*64, y*64));
        }
        if(bit[i]==BLOCK_POWER){
            scene->addItem(new BlockPower       (x*64, y*64));
        }
        if(bit[i]==PIECE){
            //scene->addItem(new Piece       (x*64, y*64));
            pieceList.append(new Piece(x*64,y*64,&pieceList));
            qDebug()<<"size piece list"<<pieceList.length();
            addedPiece.append(false);
        }
        if(bit[i]==GOOMBA){
            goombaList.append(new Enemy(x*64,y*63,"GOOMBA",&goombaList));
            qDebug()<<"size piece list"<<goombaList.length();
            addedGoomba.append(false);
        }
        i++;
        x++;
        if(x==decor_nb_BlockX){
            y++;
            x=0;
            if(y==decor_nb_BlockY){
                endFile=true;
            }
        }
    }
    fichierDecor.close();
    qDebug()<<"fin creation block";
}

//Set the connection of the game
void Game::setConnect(){
    //connect decor
    QTimer *timer1 = new QTimer();
    QObject::connect(timer1, SIGNAL(timeout()),this,SLOT(add_removeBlock()));
    timer1->start(1000 / 450);
    //Connect Advance
    QTimer *timer = new QTimer();
    if(Player::gameOver==false)QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 45);
    //Connect Goomba & Player
    for(int i = 0;i<Number_Of_Goomba;i++){
        connect(&player->pView,SIGNAL(collisionDownWithEnemy()),goombaList[i],SLOT(playerCollisionUp()));
    }

    for(int i = 0;i<Number_Of_PIRANHA_PLANTE;i++){
        connect(&player->pView,SIGNAL(collisionDownWithEnemy()),PIRANHA_PLANTE[i],SLOT(playerCollisionUp()));
    }
    connect(&player->pView,SIGNAL(collisionDownWithEnemy()),turtle,SLOT(playerCollisionUp()));
    connect(tp1,SIGNAL(sendPosTp(int,int)),&player->pView,SLOT(receiveTPsignal(int,int)));                    //Ajout 15/11
    connect(tp2,SIGNAL(sendPosTp(int,int)),&player->pView,SLOT(receiveTPsignal(int,int)));                    //Ajout 15/11
}

//Add ennemy and coin whlethe player rogress in the level
void Game::add_removeBlock(){
    double posPieceRelativeX=0;
    double posPieceRelativeY=0;

    double posGoombaRelativeX=0;
    double posGoombaRelativeY=0;

    //qDebug()<<"ADD OR REMOVE";

    for(int j=0;j<pieceList.length();j++){
        posPieceRelativeX=abs(player->pView.x()-pieceList[j]->x());
        posPieceRelativeY=abs(player->pView.y()-pieceList[j]->y());

        //qDebug()<<"ADD OR REMOVE PIECE";

        if((posPieceRelativeX < nb_pixel_displayedX || posPieceRelativeX < nb_pixel_displayedX) && (posPieceRelativeY < nb_pixel_displayedY || posPieceRelativeY < nb_pixel_displayedY) && addedPiece[j]==false){
            scene->addItem(pieceList[j]);
            addedPiece[j]=true;
            qDebug()<<"Piece Added";
        }
    }

    for(int k=0;k<goombaList.length();k++){
        posGoombaRelativeX=abs(player->pView.x()-goombaList[k]->x());
        posGoombaRelativeY=abs(player->pView.y()-goombaList[k]->y());

        //qDebug()<<"ADD OR REMOVE PIECE";

        if((posGoombaRelativeX < nb_pixel_displayedX || posGoombaRelativeX < nb_pixel_displayedX) && (posGoombaRelativeY < nb_pixel_displayedY || posGoombaRelativeY < nb_pixel_displayedY) && addedGoomba[k]==false){
            scene->addItem(goombaList[k]);
            addedGoomba[k]=true;
            connect(&player->pView,SIGNAL(collisionDownWithEnemy()),goombaList[k],SLOT(playerCollisionUp()));
            qDebug()<<"Goomba Added";
        }
    }
}
