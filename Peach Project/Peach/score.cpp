
#include "Score.h"
#include <QFont>
#include <QDebug>

Score::Score(){
    // initialize the score to 0
    score = 0;

    // draw the text
    //setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    //setDefaultTextColor(Qt::blue);
    //setFont(QFont("times",16));
}

void Score::increase(int nbCoin){
    //setPlainText(QString("Score: ") + QString::number(nbCoin)); // Score: 1
}

int Score::getScore(){
    return score;
}

void Score::scoreUpdate(){
    qDebug()<<"ca marche";
    //setPlainText(QString("Score: ") + QString::number(score++));
}

QRectF Score:: boundingRect() const {}

void Score::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
