#ifndef MAINMENU_H
#define MAINMENU_H
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QString>
#include <string>
#include "ui_mainmenu.h"
#include "iogame.h"
#include "gamecontroller.h"


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

public slots:
    void handleTetris();
    void handle2048();
    void handleExit();
    void setSettings();
    void showMainMenu();

private:
    Ui::MainMenuUi * ui;
    GameController *tetrisGame;
    list<Game> tetrisHighscores; // struct Game is defined in IOgame
    bool isBackgroundMusic;
    bool isGameSounds;
    string playername;

    void fetchHighscores();
};


#endif // MAINMENU_H
