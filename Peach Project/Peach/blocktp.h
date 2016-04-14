#ifndef BLOCKTP_H
#define BLOCKTP_H

#include <QObject>
#include <QWidget>


#include "brique.h"

class BlockTp: public QObject,public QGraphicsItem{                    //Ajout 15/11
    Q_OBJECT
public:
    BlockTp(int x, int y, int xx, int yy);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void playerCollision(QPointF pos);
    QPixmap getTextureBlock();
    void setTextureBlock(QPixmap newTextureBlock);
    void advance(int step) Q_DECL_OVERRIDE;
    void collision();
signals:
    void sendPosTp(int,int);
private:
    QPixmap texture_tuyau;

    QList <QGraphicsItem *> colliding_items;
    int posXdest;
    int posYdest;

    const static int COLLISION_SIZE =80;

    const static int TEXTURE_WIDTH = 80;
    const static int TEXTURE_HEIGHT = 90;

    const static int COLLISION_POSX = 0;   //Relatively to the visual position     //modification 14/10
    const static int COLLISION_POSY = 0;                                           // modification 14/10

};

#endif // BLOCKTP_H
