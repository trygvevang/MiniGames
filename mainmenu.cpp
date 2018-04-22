#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuUi)
{
    getGameHighscores();
    game2048 = new Controller2048;
    tetrisGame = new TetrisController;
    ui->setupUi(this);
    this->setWindowTitle("Mini Games");
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    connect(ui->tetrisButton,         SIGNAL(clicked()), this, SLOT(handleTetris()));
    connect(ui->button2048,           SIGNAL(clicked()), this, SLOT(handle2048()));
    connect(ui->deleteScoresButton,   SIGNAL(clicked()), this, SLOT(handleDeleteScores()));
    connect(ui->exitButton,           SIGNAL(clicked()), this, SLOT(handleExit()));
    QObject::connect(tetrisGame, SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
    QObject::connect(game2048,   SIGNAL(gameClosed()), this, SLOT(showMainMenu()));
    showTopTenGameScores();
}

// Get highscores for Tetris and 2048
void MainMenu::getGameHighscores()
{
    tetrisHighscores = loadGameScores("tetris_highscores.csv");
    highscores2048 = loadGameScores("highscore_2048.csv");
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
    setSettings();
    game2048->setSettings(isGameSounds, playername);
    if (highscores2048.size() > 0)
    {
        game2048->setHighscore(highscores2048.front().score);
    }
    else
        game2048->setHighscore(0);

    game2048->show();
    this->hide();
}

void MainMenu::handleDeleteScores()
{
    remove("tetris_highscores.csv");
    remove("highscore_2048.csv");
    tetrisHighscores.clear();
    highscores2048.clear();
    showTopTenGameScores();
}

void MainMenu::handleExit()
{
    this->close();
}


void MainMenu::showMainMenu()
{
    getGameHighscores();
    this->setVisible(true);

}

void MainMenu::setSettings()
{
    // Pattern: match any letter in norwegian alphabet including digit, '-' or '_'. Can include, but not start with ' ' or '!'.
    QRegExp pattern("^[a-zA-Z0-9æøåÆØÅ_-]+[a-z A-Z0-9æøåÆØÅ!_-]*$");
    isBackgroundMusic = ui->playBGMusic->isChecked();
    isGameSounds = ui->playGameSounds->isChecked();

    if (ui->playerName->text() == "" || !pattern.exactMatch(ui->playerName->text()))
    {
        playername = "Unnamed player";
    }
    else playername = ui->playerName->text().toStdString();
}

void MainMenu::showTopTenGameScores()
{
    // Clear any previous data in layout
    clearLayout(ui->topTenTetrisLayout);
    clearLayout(ui->topTen2048Layout);

    // Tetris highscores
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

    // 2048 highscores
    if (highscores2048.size() > 0)
    {
        int i = 0;
        for (Game g : highscores2048)
        {
            if (i < 10)
            {
                QLabel * game = new QLabel();
                QFont f("Arial", 16, QFont::Bold);
                QString text = QStringLiteral("%1: %2").arg(QString::fromStdString(g.playername)).arg(g.score);
                game->setText(text);
                game->setFont(f);
                ui->topTen2048Layout->addWidget(game);
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
            ui->topTen2048Layout->addWidget(game);
        }
    }
    else
    {
        QLabel * message = new QLabel();
        QFont f("Arial", 16, QFont::Bold);
        message->setText("No highscores yet.");
        message->setFont(f);
        ui->topTen2048Layout->addWidget(message);
    }
}

void MainMenu::clearLayout(QVBoxLayout * layout)
{
    QLayoutItem * item;
    while ((item = layout->takeAt(0)))
    {
        delete item->widget();
    }
    delete item;
}

MainMenu::~MainMenu()
{
    delete tetrisGame;
    delete game2048;
}
