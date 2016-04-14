#ifndef POWER_H
#define POWER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Power:public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Power(bool dir);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setTexture();

protected:
    void advance(int step);

private:
    QPixmap texturePower;

    QList <QGraphicsItem *> colliding_items;

    QMediaPlayer *powerRelease; //SOUND

    const static int COLLISION_WIDTH =400;
    const static int COLLISION_HEIGHT =157;

    const static int TEXTURE_WIDTH = 400;
    const static int TEXTURE_HEIGHT = 157;

    const static int COLLISION_POSX = 0;
    const static int COLLISION_POSY = 0;

    bool direction;

signals:

public slots:
};


#endif // POWER_H
