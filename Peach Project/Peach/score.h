#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItem>
#include <QObject>


class Score: public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Score();
    void increase(int nbCoin);
    int getScore();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
private:
    int score;
public slots:
    void scoreUpdate();
};

#endif // SCORE_H
