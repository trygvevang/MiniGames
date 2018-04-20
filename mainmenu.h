#ifndef MAINMENU_H
#define MAINMENU_H
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QString>
#include <QRegExp>
#include <string>
#include "ui_mainmenu.h"
#include "iogame.h"
#include "2048/controller/controller2048.h"
#include "tetris/controller/tetriscontroller.h"

namespace Ui
{
class MainMenuUi;
}

using namespace std;

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = 0);
    ~MainMenu();
    void setSettings();
    void showTopTenGameScores();

public slots:
    void handleTetris(); // Starts or resumes Tetris game
    void handle2048(); // Starts or resumes 2048 game
    void handleExit();
    void showMainMenu();

private:
    Ui::MainMenuUi * ui;
    TetrisController * tetrisGame;
    Controller2048 * game2048;
    list<Game> tetrisHighscores; // Struct Game is defined in IOgame
    list<Game> highscores2048;
    bool isBackgroundMusic; // Flag stating if background music is to be played
    bool isGameSounds; // Flag stating if game sounds are to be played
    string playername;

    void getGameHighscores();
};


#endif // MAINMENU_H
