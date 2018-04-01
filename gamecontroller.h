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
    Q_OBJECT
public:
    GameController(QWidget *parent = 0);
    ~GameController();
    void drawNextTile(); // draws the board with next tile
    void drawBoard(); // draws the gameboard
    void drawActiveTileOnBoard();
    void updateView();
    Tile * chooseNextTile();
    void initGame();
    void parseProps();
    void writeProps();
    void keyPressEvent(QKeyEvent * event); // Handling key input from user
public slots:
    void handleGame();
    void generation();

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
    bool isPlaying;

    QString setRectColor(int value);
};

#endif // GAMECONTROLLER_H
