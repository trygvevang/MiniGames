#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QTimer> // one "generation" in active game should last one second
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QString>
#include <random>
#include "ui_tetris.h"
#include "tile.h"
#include "itile.h"
#include "jtile.h"
#include "ltile.h"
#include "otile.h"
#include "stile.h"
#include "ttile.h"
#include "ztile.h"
#include "board.h"

namespace Ui
{
class Tetris;
}
using namespace std;

class GameController : public QWidget
{
public:
    GameController(QWidget *parent = 0);
    ~GameController();
    void drawNextTile(); // draws the board with next tile
    void drawBoard(); // draws the gameboard
    Tile * chooseNextTile();
    void initGame();
    void parseProps();
    void writeProps();
    void keyPressEvent(QKeyEvent * event); // Handling key input from user
private:
    Ui::Tetris * ui;
    QGraphicsScene * boardScene;
    QGraphicsScene * nextTileScene;
    QTimer * timer;

    Board * board;
    Tile * activeTile;
    Tile * nextTile;
    int score;
    int highScore;

    QString setRectColor(int value);
};

#endif // GAMECONTROLLER_H
