#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "brique.h"
#include "enemy.h"
#include "gameview.h"
#include "piece.h"
#include "blocklimit.h"
#include "blocktp.h"
#include "turtle.h"

#define Screen_sizeX 1408
#define Screen_sizeY 960

#define Decor1 ":/decors/Decor1.txt"                    //Ajout 15/11
#define Decor2 ":/decors/Decor2.txt"                    //Ajout 15/11

#define Decor1_nb_BlockX 195
#define Decor1_nb_BlockY 18
#define Number_Of_Goomba 5
#define Number_Of_PIRANHA_PLANTE 0
#define BLOCK_MARRON '1'
#define BLOCK_LIMIT '2'
#define BLOCK_SURPRISE '3'
#define BLOCK_HEART '4'
#define BLOCK_DESTRUCTIBLE '5'
#define BLOCK_POWER '6'
#define PIECE '7'
#define GOOMBA '8'

#define nb_pixel_displayedX 704
#define nb_pixel_displayedY 704

class Game : public QWidget
{
    Q_OBJECT
public:

    Game(QGraphicsScene* scene);
    QGraphicsView view;
    QGraphicsView viewHud;
    QGraphicsScene *scene;

    Enemy *Goomba[Number_Of_Goomba];
    Enemy *PIRANHA_PLANTE[Number_Of_PIRANHA_PLANTE];

    QList <Brique *> blockList;
    QList <bool> addedBlock;

    QList <Piece *> pieceList;
    QList <bool> addedPiece;

    QList <Enemy *> goombaList;
    QList <bool> addedGoomba;


    Player * player;
    Health * health;
    BlockTp *tp1;                    //Ajout 15/11
    BlockTp *tp2;                    //Ajout 15/11
    Turtle * turtle;


public slots:
    void add_removeBlock();
private:
    int decor_nb_BlockX;                    //Ajout 15/11
    int decor_nb_BlockY;                    //Ajout 15/11
    QString filename;                    //Ajout 15/11
    void setView(QGraphicsScene* scene);
    void setEnemy();
    void setPlayer();
    void setBlock();
    void setConnect();
};

#endif // GAME_H
