
#include <QApplication>
#include "Game.h"
#include <QLabel>

Game *game;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QGraphicsScene scene;

    //The object game contains the QGraphicsView which contains the QGraphicsScene
    Game game(&scene);

    game.view.show();
    return app.exec();
}
