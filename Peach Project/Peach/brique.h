#ifndef BRIQUE_H
#define BRIQUE_H

#include <QObject>
#include <QGraphicsItem>

class Brique: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Brique(int x, int y);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QPixmap getTextureBlock();
    void setTextureBlock(QPixmap newTextureBlock);

private:
    QPixmap texture_block;

    const static int COLLISION_SIZE =64;

    const static int TEXTURE_WIDTH = 64;
    const static int TEXTURE_HEIGHT = 64;

    const static int COLLISION_POSX = 0;   //Relatively to the visual position     //modification 14/10
    const static int COLLISION_POSY = 0;                                           // modification 14/10

};


#endif // BRIQUE_H
