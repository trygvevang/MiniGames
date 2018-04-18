#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QRandomGenerator>
#include <list>
#include "ui_tetris.h"
#include "iogame.h"
#include "../model/tile.h"
#include "../model/itile.h"
#include "../model/jtile.h"
#include "../model/ltile.h"
#include "../model/otile.h"
#include "../model/stile.h"
#include "../model/ttile.h"
#include "../model/ztile.h"
#include "../model/board.h"

namespace Ui
{
class Tetris;
}
using namespace std;

class TetrisController : public QWidget
{
    Q_OBJECT
public:
    TetrisController(QWidget *parent = 0);
    ~TetrisController();
    void drawSmallViewTile(Tile *tile, QGraphicsView *gView, QGraphicsScene *scene); // draws the "next tile"-board and "hold tile"-board with its respective tile
    void drawBoard(); // draws the gameboard
    void drawTileOnBoard(Tile *tile, bool isOpacity); // draws active tile on gameboard
    void drawGhostTile(); // draws lowest valid y-position of active tile on gameboard according to its x-position
    void drawGameOver(); // draws game over on top of gameboard
    void updateView();
    Tile * chooseNextTile();
    void reloadGame();
    void setupGame();
    void keyPressEvent(QKeyEvent * event); // Handling key input from user
    void keyReleaseEvent(QKeyEvent *event); //Handling key releases from user
    void saveHighscore();
    void setSettings(bool isBackgroundMusic, bool isGameSounds, string playername);
    void setHighscore(int highscore);
    void switchHoldTile();

public slots:
    void handleGame(); // Handles game when pressing play/pause-button
    void generation(); // When QTimer times out
    void handleMenuSettings();
    void handleRestart();

signals:
    bool gameClosed();

private:
    // Graphical user interface
    Ui::Tetris * ui;
    QGraphicsScene * boardScene;
    QGraphicsScene * nextTileScene;
    QGraphicsScene * holdTileScene;
    QTimer * timer;

    // Sounds
    QMediaPlaylist * playlist;
    QMediaPlayer * backgroundMusic;
    QMediaPlayer * rowDeletedSound;
    QMediaPlayer * slamTileSound;
    QMediaPlayer * rotateSound;
    QMediaPlayer * gameOverSound;

    // Board and tiles
    Board * board;
    Tile * activeTile;
    Tile * nextTile;
    Tile * ghostTile;
    Tile * nextGhostTile;
    Tile * holdTile;

    QRandomGenerator rand;

    // Miscellaneous game data
    int score;
    int highScore;
    bool isPlaying;
    bool isGameOver;
    bool isSoftDrop;
    bool holdTileGen; //switchHoldTile can only be pressed once per placeTileOnBoard
    static constexpr int SOFT_DROP_SPEED = 100; // 100 ms
    int gameInterval; // interval between vertical movements
    int level;
    int rowsCompleted;
    vector<int> randomBag;

    // Settings
    bool isBackgroundMusic;
    bool isGameSounds;
    string playername;

    // Private helper functions
    QString setRectColor(int value);
    void calculateScore(int rows);
};

#endif // GAMECONTROLLER_H
