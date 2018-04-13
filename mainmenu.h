#ifndef MAINMENU_H
#define MAINMENU_H
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QString>
#include "ui_mainmenu.h"
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
    void showMainMenu();

private:
    Ui::MainMenuUi * ui;

    GameController *tetrisGame;


};


#endif // MAINMENU_H
