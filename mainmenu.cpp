#include "mainmenu.h"
#include "gamecontroller.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    tetrisGame = new GameController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    connect(ui->btn_tetris,     SIGNAL(clicked()), this, SLOT(btnTetris()));
    connect(ui->btn_exit,       SIGNAL(clicked()), this, SLOT(btnExit()));
    connect(ui->btn_2048,       SIGNAL(clicked()), this, SLOT(btn2048()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
}

void MainMenu::btnTetris()
{
    tetrisGame->show();
    this->hide();
}

void MainMenu::btn2048()
{

}

void MainMenu::btnExit()
{
    this->close();
}

void MainMenu::showMainMenu(){
    this->setVisible(true);

}


MainMenu::~MainMenu()
{

}
