#include "enemyview.h"
#include <QList>

EnemyView::EnemyView()
{
    animGoombaL.append(QPixmap(":/images/goombaR_1.png"));
    animGoombaL.append(QPixmap(":/images/goombaR_2.png"));
    animGoombaL.append(QPixmap(":/images/goombaR_3.png"));
    animGoombaL.append(QPixmap(":/images/goombaR_4.png"));
    animGoombaL.append(QPixmap(":/images/goombaR_5.png"));

    animGoombaR.append(QPixmap(":/images/goombaL_1.png"));
    animGoombaR.append(QPixmap(":/images/goombaL_2.png"));
    animGoombaR.append(QPixmap(":/images/goombaL_3.png"));
    animGoombaR.append(QPixmap(":/images/goombaL_4.png"));
    animGoombaR.append(QPixmap(":/images/goombaL_5.png"));
}

EnemyView::~EnemyView(){
    animGoombaL.clear();
    animGoombaR.clear();
}

QPixmap EnemyView::setPlantePiranhaViewRight(){
    return QPixmap(":/images/PlantePiranhaR.png");
}
QPixmap EnemyView::setPlantePiranhaViewLeft(){
    return QPixmap(":/images/PlantePiranhaL.png");
}

QPixmap EnemyView::getTextureGoombaR(int animation){
    return animGoombaR.value(animation);
}
QPixmap EnemyView::getTextureGoombaL(int animation){
    return animGoombaL.value(animation);
}
