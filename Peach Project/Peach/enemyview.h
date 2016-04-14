#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

class EnemyView
{
public:
    EnemyView();
    ~EnemyView();

    QList <QPixmap> animGoombaL;
    QList <QPixmap> animGoombaR;

    QPixmap getTextureGoombaR(int animation);
    QPixmap getTextureGoombaL(int animation);

    QPixmap setPlantePiranhaViewLeft();
    QPixmap setPlantePiranhaViewRight();
};

#endif // ENEMYVIEW_H
