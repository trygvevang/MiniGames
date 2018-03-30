#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>
#include <QTimer> // one "generation" in active game should last one second
#include <QKeyEvent>
#include <random>
#include "tile.h"
#include "itile.h"
#include "jtile.h"
#include "ltile.h"
#include "otile.h"
#include "stile.h"
#include "ttile.h"
#include "ztile.h"
#include "board.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController();
    ~GameController();
    void drawNextTile(); // draws the board with next tile
    void drawBoard(); // draws the gameboard
    Tile * chooseNextTile();
    void initGame();
    void parseProps();
    void writeProps();
    void keyPressEvent(); // Handling key input from user
private:
    Board board;
    Tile * activeTile;
    Tile * nextTile;
    int score;
    int highScore;
};

#endif // GAMECONTROLLER_H
