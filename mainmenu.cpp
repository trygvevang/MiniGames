#include "mainmenu.h"
#include "gamecontroller.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    tetrisGame = new GameController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    connect(ui->tetrisButton,     SIGNAL(clicked()), this, SLOT(handleTetris()));
    connect(ui->exitButton,       SIGNAL(clicked()), this, SLOT(handleExit()));
    connect(ui->button2048,       SIGNAL(clicked()), this, SLOT(handle2048()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
}

void MainMenu::handleTetris()
{
    tetrisGame->show();
    this->hide();
}

void MainMenu::handle2048()
{

}

void MainMenu::handleExit()
{
    this->close();
}

void MainMenu::showMainMenu(){
    this->setVisible(true);

}


MainMenu::~MainMenu()
{

}
