#ifndef TURTLEVIEW_H
#define TURTLEVIEW_H

#include <QPixmap>

class TurtleView
{
public:
    TurtleView();

    QList <QPixmap> animTurtleL;
    QList <QPixmap> animTurtleR;

    QPixmap getTextureTurtleR(int animation);
    QPixmap getTextureTurtleL(int animation);

    QPixmap getTextureShellR();
    QPixmap getTextureShellL();
};
#endif // TURTLEVIEW_H
