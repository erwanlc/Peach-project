#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Piece: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Piece(int x, int y, QList <Piece*>* pPiece,QGraphicsItem * parent=0);
    ~Piece();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void advance(int step);

private:
    QPixmap textureCoin;

    QList <Piece*>* pieceListPiece;

    QList <QGraphicsItem *> colliding_items;

    QMediaPlayer * coinCatch; //SOUND

    const static int COLLISION_SIZE =64;

    const static int TEXTURE_WIDTH = 64;
    const static int TEXTURE_HEIGHT = 64;

    const static int COLLISION_POSX = 0;
    const static int COLLISION_POSY = 0;
};


#endif // PIECE_H

