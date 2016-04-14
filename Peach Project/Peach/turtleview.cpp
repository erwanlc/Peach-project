#include "turtleview.h"

TurtleView::TurtleView()
{
    animTurtleL.append(QPixmap(":/images/turtleL_1.png"));
    animTurtleL.append(QPixmap(":/images/turtleL_2.png"));
    animTurtleL.append(QPixmap(":/images/turtleL_3.png"));
    animTurtleL.append(QPixmap(":/images/turtleL_4.png"));
    animTurtleL.append(QPixmap(":/images/turtleL_5.png"));

    animTurtleR.append(QPixmap(":/images/turtleR_1.png"));
    animTurtleR.append(QPixmap(":/images/turtleR_2.png"));
    animTurtleR.append(QPixmap(":/images/turtleR_3.png"));
    animTurtleR.append(QPixmap(":/images/turtleR_4.png"));
    animTurtleR.append(QPixmap(":/images/turtleR_5.png"));
}

QPixmap TurtleView::getTextureTurtleR(int animation){
    return animTurtleR.value(animation);
}
QPixmap TurtleView::getTextureTurtleL(int animation){
    return animTurtleL.value(animation);
}
QPixmap TurtleView::getTextureShellR(){
    return QPixmap(":/images/turtleR_hide.png");
}
QPixmap TurtleView::getTextureShellL(){
    return QPixmap(":/images/turtleL_hide.png");
}
