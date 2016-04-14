#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QPixmap>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
private:
    int health;
    QPixmap texture;
};

#endif // HEALTH_H
