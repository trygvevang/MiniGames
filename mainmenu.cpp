#include "mainmenu.h"
#include "gamecontroller.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    fetchHighscores();
    tetrisGame = new GameController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    connect(ui->tetrisButton,         SIGNAL(clicked()), this, SLOT(handleTetris()));
    connect(ui->exitButton,           SIGNAL(clicked()), this, SLOT(handleExit()));
    connect(ui->button2048,           SIGNAL(clicked()), this, SLOT(handle2048()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
    showTopTen();
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

void MainMenu::showTopTen()
{
    // TODO: if there are no highscores show it
    int i = 0;
    for (Game g : tetrisHighscores)
    {
        if (i < 10)
        {
            QLabel * game = new QLabel();
            QFont f("Arial", 16, QFont::Bold);
            QString text = QStringLiteral("Player: %1, score: %2").arg(QString::fromStdString(g.playername)).arg(g.score);
            game->setText(text);
            game->setFont(f);
            game->move(10, (i * ui->topTenTetris->height()/10));
            ui->topTenTetrisLayout->addWidget(game);
        }
        else break;
        i++;
    }
    /*
    QLabel * gameOverLabel = new QLabel();
    QFont f( "Arial", 40, QFont::Bold);
    gameOverLabel->setText("Game Over");
    gameOverLabel->setFont(f);
    gameOverLabel->move((width/2)-(gameOverLabel->sizeHint().width()/2), (height/2)-(gameOverLabel->sizeHint().height()/2));
    gameOverLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: black;");
    boardScene->addWidget(gameOverLabel);
    */
}

MainMenu::~MainMenu()
{
    delete tetrisGame;
}
