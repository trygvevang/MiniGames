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
#include "board2048.h"

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

public slots:
    void handleRestart();
    void handleMenuSettings();

signals:
    bool gameClosed();

private:
    Ui::UI2048 * ui;
    QGraphicsScene * boardScene;
    Board2048 *board;
    int score;
    int highScore;

};

#endif // CONTROLLER2048_H
