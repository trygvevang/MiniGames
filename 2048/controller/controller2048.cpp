#include "controller2048.h"
#include <QDebug>

Controller2048::Controller2048(QWidget *parent) : QWidget(parent), ui(new Ui::UI2048)
{
    ui->setupUi(this);
    ui->boardView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->boardView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->boardView->setFocus();
    boardScene = new QGraphicsScene(this);

    ui->boardView->setScene(boardScene);

    boardScene->setSceneRect(0,0,350,350);
    ui->boardView->setSceneRect(boardScene->sceneRect());

    moveSound = new QMediaPlayer();
    gameOverSound = new QMediaPlayer();

    moveSound->setMedia(QUrl("qrc:/sounds/Sound/waterdrop.wav"));
    gameOverSound->setMedia(QUrl("qrc:/sounds/Sound/game_over.wav"));

    connect(ui->backToMenuButton, SIGNAL(clicked()), this, SLOT(handleMenuSettings()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(handleRestart()));
    setupGame();
}

void Controller2048::setupGame()
{
    board = new Board2048;
    score = 0;
    gameOver = false;

    if (gameOverSound->state() == QMediaPlayer::PlayingState)
    {
        gameOverSound->stop();
    }

    QString scoreText = QStringLiteral("Score: %1").arg(score);
    ui->scoreLabel->setText(scoreText);
    drawBoard();
}

void Controller2048::drawBoard()
{
    boardScene->clear();
    int cellHeight = (ui->boardView->height())/board->BOARD_SIZE;
    int cellWidth = (ui->boardView->width())/board->BOARD_SIZE;

    for(int r = 0; r < board->BOARD_SIZE; r++){
        for(int c = 0; c < board->BOARD_SIZE; c++){
            QGraphicsRectItem * rect = new QGraphicsRectItem();
            rect->setRect(c*cellWidth, r*cellHeight, cellWidth, cellHeight);

            boardScene->addItem(rect);
            QLabel *rectValue = new QLabel;

            if(board->getBoard()[r][c] != 0)
            {
                rectValue->setGeometry(c*cellWidth, r*cellHeight, cellWidth, cellHeight);
                QString path = ":/images/Images/tile" + QString::number(board->getBoard()[r][c]) + ".png";
                QPixmap pix(path);
                rectValue->setPixmap(pix);

                boardScene->addWidget(rectValue);
            }
        }
    }
}

void Controller2048::drawGameOver()
{
    int width = ui->boardView->width();
    int height = ui->boardView->height();

    //Draw background
    QGraphicsRectItem * gameOverRect = new QGraphicsRectItem();
    gameOverRect->setRect(0, 0, width, height);
    QBrush brush(Qt::SolidPattern);
    QColor color("#838584");
    color.setAlpha(212);
    brush.setColor(color);
    gameOverRect->setBrush(brush);

    //Draw label "Game Over"
    QLabel * gameOverLabel = new QLabel();
    QFont f( "Arial", 40, QFont::Bold);
    gameOverLabel->setText("Game Over");
    gameOverLabel->setFont(f);
    gameOverLabel->move((width/2)-(gameOverLabel->sizeHint().width()/2), (height/2)-(gameOverLabel->sizeHint().height()/2));
    gameOverLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: black;");


    //Add items to scene
    boardScene->addItem(gameOverRect);
    boardScene->addWidget(gameOverLabel);
}

void Controller2048::keyPressEvent(QKeyEvent * event)
{
    if(!gameOver){
        // 1 = left, 2 = down, 3 = right, 4 = up
        if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        {
            handleRound(1);
        }
        else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        {
            handleRound(2);
        }
        else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        {
            handleRound(3);
        }
        else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        {
            handleRound(4);
        }
    }
}

void Controller2048::handleRound(int direction)
{
    int roundScore = board->round(direction);
    if(roundScore >= 1)
    {
        //play tunes
        if (moveSound->state() == QMediaPlayer::PlayingState && isGameSounds)
        {
            moveSound->setPosition(0);
        }
        else if ((moveSound->state() == QMediaPlayer::PausedState || moveSound->state() == QMediaPlayer::StoppedState) && isGameSounds)
        {
            moveSound->play();
        }

        if(roundScore > 1)
            score += roundScore;
        QString scoreText = QStringLiteral("Score: %1").arg(score);
        ui->scoreLabel->setText(scoreText);
        drawBoard();
    }
    else if(roundScore < 0) //Game over
    {
        if (isGameSounds)
            gameOverSound->play();
        gameOver = true;
        drawGameOver();
        return;
    }

}
void Controller2048::handleRestart()
{
    saveHighscore();
    delete board;
    setupGame();
}

void Controller2048::handleMenuSettings()
{
    emit gameClosed();
    this->close();
}

void Controller2048::saveHighscore()
{
    if (score > highScore)
    {
        saveGameScore(playername, score, "highscore_2048.csv");
        highScore = score;
    }
}

void Controller2048::setSettings(bool isGameSounds, string playername)
{
    this->playername = playername;
    this->isGameSounds = isGameSounds;
}

void Controller2048::setHighscore(int highscore)
{
    this->highScore = highscore;
    QString highscoreText = QStringLiteral("Highscore: %1").arg(highScore);
    ui->highscoreLabel->setText(highscoreText);
}

Controller2048::~Controller2048()
{
    saveHighscore();
    delete board;
    delete moveSound;
    delete gameOverSound;
}

