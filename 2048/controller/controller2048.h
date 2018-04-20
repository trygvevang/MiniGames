#ifndef CONTROLLER2048_H
#define CONTROLLER2048_H
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QColor>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "ui_2048.h"
#include "../model/board2048.h"
#include "iogame.h"

namespace Ui
{
class UI2048;
}

using namespace std;

class Controller2048 : public QWidget
{
    Q_OBJECT
public:
    Controller2048(QWidget *parent = 0);
    ~Controller2048();

    void drawBoard();
    void keyPressEvent(QKeyEvent * event);
    void setupGame();
    void saveHighscore();
    void setSettings(string playername);
    void setHighscore(int highScore);

public slots:
    void handleRestart();
    void handleMenuSettings();

signals:
    bool gameClosed();

private:
    Ui::UI2048 * ui;
    QGraphicsScene * boardScene;
    Board2048 *board;
    string playername;
    int score;
    int highScore;

    void handleRound(int direction);
};

#endif // CONTROLLER2048_H
