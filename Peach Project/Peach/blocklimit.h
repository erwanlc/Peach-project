#ifndef BLOCKLIMIT_H
#define BLOCKLIMIT_H

#include "brique.h"

class BlockLimit:public Brique
{
public:
    BlockLimit(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    int posX;
    int posY;
};

#endif // BLOCKLIMIT_H
