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
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <random>
#include <list>
#include "ui_tetris.h"
#include "iogame.h"
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
    void drawGhostTile();
    void updateView();
    Tile * chooseNextTile();
    void initGame();
    void reloadGame();
    void setupGame();
    void parseProps();
    void writeProps();
    void keyPressEvent(QKeyEvent * event); // Handling key input from user
    void keyReleaseEvent(QKeyEvent *event); //Handling key releases from user
    void saveHighscore();
    void drawGameOver();
    
public slots:
    void handleGame();
    void generation();

private:
    Ui::Tetris * ui;
    QGraphicsScene * boardScene;
    QGraphicsScene * nextTileScene;
    QTimer * timer;
    QMediaPlaylist * playlist;
    QMediaPlayer * player;
    QMediaPlayer * rowDeletedSound;
    QMediaPlayer * slamTileSound;
    QMediaPlayer * rotateSound;

    Board * board;
    Tile * activeTile;
    Tile * nextTile;
    Tile * ghostTile;
    Tile * nextGhostTile;
    int score;
    int highScore;
    bool isPlaying;
    bool isGameOver;
    int softDropSpeed;
    int gameInterval;
    int level;
    list<Game> highscores; // struct Game is defined in IOgame
    int rowsCompleted;
    bool isSoftDrop;

    QString setRectColor(int value);
    void calculateScore(int rows);
};

#endif // GAMECONTROLLER_H
