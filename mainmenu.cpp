#include "mainmenu.h"
#include "gamecontroller.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    fetchHighscores();
    tetrisGame = new GameController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    connect(ui->tetrisButton,         SIGNAL(clicked()), this, SLOT(handleTetris()));
    connect(ui->exitButton,           SIGNAL(clicked()), this, SLOT(handleExit()));
    connect(ui->button2048,           SIGNAL(clicked()), this, SLOT(handle2048()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
    setSettings();
}

// Get highscores for Tetris and 2048
void MainMenu::fetchHighscores()
{
    tetrisHighscores = loadScores("highscores.csv");
    // TODO: fetch highscores for 2048
}

void MainMenu::handleTetris()
{
    setSettings();
    tetrisGame->setSettings(isBackgroundMusic, isGameSounds, playername);

    if (tetrisHighscores.size() > 0)
    {
        tetrisGame->setHighscore(tetrisHighscores.front().score);
    }
    else
        tetrisGame->setHighscore(0);

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


void MainMenu::showMainMenu()
{
    this->setVisible(true);
}

void MainMenu::setSettings()
{
    isBackgroundMusic = ui->playBGMusic->isChecked();
    isGameSounds = ui->playGameSounds->isChecked();
    if (ui->playerName->text() == "")
    {
        playername = "Unnamed player";
    }
    else playername = ui->playerName->text().toStdString();
}

MainMenu::~MainMenu()
{

}
