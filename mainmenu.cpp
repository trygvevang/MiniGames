#include "mainmenu.h"
#include "gamecontroller.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    getGameHighscores();
    tetrisGame = new GameController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    connect(ui->tetrisButton,         SIGNAL(clicked()), this, SLOT(handleTetris()));
    connect(ui->exitButton,           SIGNAL(clicked()), this, SLOT(handleExit()));
    connect(ui->button2048,           SIGNAL(clicked()), this, SLOT(handle2048()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
    showTopTenGameScores();
}

// Get highscores for Tetris and 2048
void MainMenu::getGameHighscores()
{
    tetrisHighscores = loadGameScores("tetris_highscores.csv");
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

void MainMenu::showTopTenGameScores()
{
    if (tetrisHighscores.size() > 0)
    {
        int i = 0;
        for (Game g : tetrisHighscores)
        {
            if (i < 10)
            {
                QLabel * game = new QLabel();
                QFont f("Arial", 16, QFont::Bold);
                QString text = QStringLiteral("%1: %2").arg(QString::fromStdString(g.playername)).arg(g.score);
                game->setText(text);
                game->setFont(f);
                ui->topTenTetrisLayout->addWidget(game);
            }
            else break;
            i++;
        }
        for(;i < 10;i++){
            QLabel * game = new QLabel();
            QFont f("Arial", 16, QFont::Bold);
            QString text = QStringLiteral("");
            game->setText(text);
            game->setFont(f);
            ui->topTenTetrisLayout->addWidget(game);
        }
    }
    else
    {
        QLabel * message = new QLabel();
        QFont f("Arial", 16, QFont::Bold);
        message->setText("No highscores yet.");
        message->setFont(f);
        ui->topTenTetrisLayout->addWidget(message);
    }

    // TODO top ten scores for 2048
}

MainMenu::~MainMenu()
{
    delete tetrisGame;
}
