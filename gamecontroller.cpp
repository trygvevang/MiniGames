#include "gamecontroller.h"
#include <QDebug>
#include <QRandomGenerator>
#include <sys/time.h>
#include <cmath>


GameController::GameController(QWidget *parent) : QWidget(parent), ui(new Ui::Tetris)
{
    ui->setupUi(this);
    ui->graphicsView->setFocus();
    boardScene = new QGraphicsScene(this);
    nextTileScene = new QGraphicsScene(this);
    holdTileScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(boardScene);
    ui->graphicsView_2->setScene(nextTileScene);
    ui->graphicsView_hold->setScene(holdTileScene);

    boardScene->setSceneRect(0, 0, 300, 600);
    nextTileScene->setSceneRect(0, 0, 150, 150);

    ui->graphicsView->setSceneRect(boardScene->sceneRect());
    ui->graphicsView_2->setSceneRect(nextTileScene->sceneRect());
    initGame();

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(handleGame()));
    connect(timer, SIGNAL(timeout()), this, SLOT(generation()));
    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(handleRestart()));
    connect(ui->menuSettingsButton, SIGNAL(clicked()), this, SLOT(handleMenuSettings()));

    playlist = new QMediaPlaylist();
    backgroundMusic = new QMediaPlayer();
    rowDeletedSound = new QMediaPlayer();
    slamTileSound = new QMediaPlayer();
    rotateSound = new QMediaPlayer();
    gameOverSound = new QMediaPlayer();

    playlist->addMedia(QUrl("qrc:/sounds/Sound/tetris_ukulele.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    backgroundMusic->setPlaylist(playlist);
    rowDeletedSound->setMedia(QUrl("qrc:/sounds/Sound/full-row.mp3"));
    slamTileSound->setMedia(QUrl("qrc:/sounds/Sound/slam-tile.wav"));
    rotateSound->setMedia(QUrl("qrc:/sounds/Sound/rotate.wav"));
    gameOverSound->setMedia(QUrl("qrc:/sounds/Sound/game_over.wav"));
}

void GameController::drawNextTile()
{
    int tileSize = ui->graphicsView_2->width()/5;
    int viewHeight = ui->graphicsView_2->height();
    int viewWidth = ui->graphicsView_2->width();
    int tileHeightOffset = (viewHeight - (nextTile->getShape().size() * tileSize))/2;
    int tileWidthOffset = (viewWidth - (nextTile->getShape()[0].size() * tileSize))/2;


    // Draw each rectangle of next tile
    for (unsigned int i = 0; i < nextTile->getShape().size(); i++)
        {
            for (unsigned int j = 0; j < nextTile->getShape()[0].size(); j++)
            {
                if (nextTile->getShape()[i][j] != 0)
                {
                    QGraphicsRectItem * rect = new QGraphicsRectItem();
                    rect->setRect(j * tileSize + tileWidthOffset, i * tileSize + tileHeightOffset, tileSize, tileSize);

                    QBrush brush(Qt::SolidPattern);
                    const QColor color(setRectColor(nextTile->getShape()[i][j]));
                    brush.setColor(color);
                    rect->setBrush(brush);

                    nextTileScene->addItem(rect);
                }
            }
        }
}

void GameController::drawBoard()
{
    int boardWidth = ui->graphicsView->width()/board->COLS;
    int boardHeight = ui->graphicsView->height()/board->ROWS;
    for (int i = 0; i < board->ROWS; i++)
    {
        for (int j = 0; j < board->COLS; j++)
        {
            QGraphicsRectItem * rect = new QGraphicsRectItem();
            rect->setRect(j * boardWidth, i * boardHeight, boardWidth, boardHeight);

            if (board->getBoard()[i][j] != 0)
            {
                QBrush brush(Qt::SolidPattern);
                const QColor color(setRectColor(board->getBoard()[i][j]));
                brush.setColor(color);
                rect->setBrush(brush);
            }

            boardScene->addItem(rect);

        }
    }
}

void GameController::drawGhostTile(){
    ghostTile->setYPos(activeTile->getYPos());
    board->slamTile(ghostTile); //Move ghost tile to final position

    int boardWidth = ui->graphicsView->width()/board->COLS;
    int boardHeight = ui->graphicsView->height()/board->ROWS;

    // Draw each rectangle of ghost tile
    for (unsigned int i = 0; i < ghostTile->getShape().size(); i++)
    {
        for (unsigned int j = 0; j < ghostTile->getShape()[0].size(); j++)
        {
            if (ghostTile->getShape()[i][j] != 0)
            {
                QGraphicsRectItem * rect = new QGraphicsRectItem();
                rect->setRect((j + ghostTile->getXPos()) * boardWidth , (i + ghostTile->getYPos()) * boardHeight, boardWidth, boardHeight);

                QBrush brush(Qt::SolidPattern);
                QColor color(setRectColor(ghostTile->getShape()[i][j]));
                color.setAlpha(100);
                const QColor constColor = color;
                brush.setColor(constColor);
                rect->setBrush(brush);

                boardScene->addItem(rect);
            }
        }
    }
}

void GameController::drawHoldTile(Tile * nextHoldTile)
{
    int tileSize = ui->graphicsView_hold->width()/5;
    int viewHeight = ui->graphicsView_hold->height();
    int viewWidth = ui->graphicsView_hold->width();
    int tileHeightOffset = (viewHeight - (nextHoldTile->getShape().size() * tileSize))/2;
    int tileWidthOffset = (viewWidth - (nextHoldTile->getShape()[0].size() * tileSize))/2;

    // Draw each tile of tile to be held
    for (unsigned int i = 0; i < nextHoldTile->getShape().size(); i++)
        {
            for (unsigned int j = 0; j < nextHoldTile->getShape()[0].size(); j++)
            {
                if (nextHoldTile->getShape()[i][j] != 0)
                {
                    QGraphicsRectItem * rect = new QGraphicsRectItem();
                    rect->setRect(j * tileSize + tileWidthOffset, i * tileSize + tileHeightOffset, tileSize, tileSize);

                    QBrush brush(Qt::SolidPattern);
                    const QColor color(setRectColor(nextHoldTile->getShape()[i][j]));
                    brush.setColor(color);
                    rect->setBrush(brush);

                    holdTileScene->addItem(rect);
                }
            }
        }
}

void GameController::drawActiveTileOnBoard()
{
    int boardWidth = ui->graphicsView->width()/board->COLS;
    int boardHeight = ui->graphicsView->height()/board->ROWS;
    for (unsigned int i = 0; i < activeTile->getShape().size(); i++)
    {
        for (unsigned int j = 0; j < activeTile->getShape()[0].size(); j++)
        {
            if (activeTile->getShape()[i][j] != 0)
            {
                QGraphicsRectItem * rect = new QGraphicsRectItem();
                rect->setRect((j + activeTile->getXPos()) * boardWidth , (i + activeTile->getYPos()) * boardHeight, boardWidth, boardHeight);

                QBrush brush(Qt::SolidPattern);
                const QColor color(setRectColor(activeTile->getShape()[i][j]));
                brush.setColor(color);
                rect->setBrush(brush);

                boardScene->addItem(rect);
            }
        }
    }
}

void GameController::drawGameOver(){

    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    QGraphicsRectItem * gameOverRect = new QGraphicsRectItem();
    gameOverRect->setRect(0, 0, width, height);
    QBrush brush(Qt::SolidPattern);
    QColor color("#838584");
    color.setAlpha(212);
    brush.setColor(color);
    gameOverRect->setBrush(brush);
    boardScene->addItem(gameOverRect);
    QLabel * gameOverLabel = new QLabel();
    QFont f( "Arial", 40, QFont::Bold);
    gameOverLabel->setText("Game Over");
    gameOverLabel->setFont(f);
    gameOverLabel->move((width/2)-(gameOverLabel->sizeHint().width()/2), (height/2)-(gameOverLabel->sizeHint().height()/2));
    gameOverLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0); color: black;");
    boardScene->addWidget(gameOverLabel);
}

QString GameController::setRectColor(int value)
{
    QString color;
    switch (value) {
    case 1:
        color = "#00ffff";
        break;
    case 2:
        color = "#0000ff";
        break;
    case 3:
        color = "#ffa500";
        break;
    case 4:
        color = "#FFF504";
        break;
    case 5:
        color = "#00D11B";
        break;
    case 6:
        color = "#551A8B";
        break;
    default:
        color = "#ff0000";
        break;
    }
    return color;
}

Tile* GameController::chooseNextTile()
{
    rand = QRandomGenerator::securelySeeded();
    int randomIndex;
    if(randomBag.size() < 1){
        while(randomBag.size() < 7){
            bool isUnique = true;
            randomIndex = (rand.operator ()() % 7);
            foreach (int t, randomBag) {
                if(randomIndex == t)
                    isUnique = false;
            }
            if(isUnique) randomBag.push_back(randomIndex);
        }
    }
    Tile* tile;
    switch (randomBag.back()) {
    case 0:
        tile = new ITile();
        nextGhostTile = new ITile();
        break;
    case 1:
        tile = new JTile();
        nextGhostTile = new JTile();
        break;
    case 2:
        tile = new OTile();
        nextGhostTile = new OTile();
        break;
    case 3:
        tile = new LTile();
        nextGhostTile = new LTile();
        break;
    case 4:
        tile = new STile();
        nextGhostTile = new STile();
        break;
    case 5:
        tile = new TTile();
        nextGhostTile = new TTile();
        break;
    default:
        tile = new ZTile();
        nextGhostTile = new ZTile();
        break;
    }
    randomBag.pop_back();
    return tile;
}

void GameController::initGame()
{
    timer = new QTimer(this);
    setupGame();
}

void GameController::setupGame(){
    score = 0;
    level = 1; // starting level = 1
    rowsCompleted = 0;
    isGameOver = false;
    activeTile = chooseNextTile();
    ghostTile = nextGhostTile;
    nextTile = chooseNextTile();
    board = new Board();
    gameInterval = (pow(0.8-((level-1)*0.007), (level-1))*1000);
    isSoftDrop = false;
    holdTileGen = false;
    QString highscoreText = QStringLiteral("Highscore: %1").arg(highScore);
    ui->scoreLabel->setText("Score: 0");
    ui->highscoreLabel->setText(highscoreText);
    ui->levelLabel->setText("Level: 1");

    holdTile = NULL;
    holdTileScene->clear();
    drawNextTile();
    drawBoard();
    drawActiveTileOnBoard();
    drawGhostTile();
}

void GameController::reloadGame(){
    randomBag.clear();
    saveHighscore();
    setupGame();
    if (gameOverSound->state() == QMediaPlayer::PlayingState)
    {
        gameOverSound->stop();
    }
}

void GameController::handleRestart()
{
    timer->stop();
    backgroundMusic->stop();
    isPlaying = false;
    isGameOver = false;
    ui->playButton->setText("Play");
    nextTileScene->clear();
    boardScene->clear();
    reloadGame();
}

void GameController::handleGame()
{
    if (!isPlaying && !isGameOver)
    {
        timer->start(gameInterval);
        ui->board->setFocus();
        isPlaying = true;
        ui->playButton->setText("Pause");
        if (isBackgroundMusic)
            backgroundMusic->play();
        ui->restartButton->setVisible(true);
    }
    else if(isPlaying && !isGameOver)
    {
        timer->stop();
        isPlaying = false;
        ui->playButton->setText("Resume");
        backgroundMusic->pause();
    }else{
        timer->start(gameInterval);
        isPlaying = true;
        isGameOver = false;
        ui->playButton->setText("Pause");
        if (isBackgroundMusic)
            backgroundMusic->play();
        nextTileScene->clear();
        boardScene->clear();
        reloadGame();
        ui->restartButton->setVisible(true);
    }
}

void GameController::generation()
{

    // Next genereation
    if (!board->isGameOver(activeTile))
    {
        if (board->isVerticalMoveValid(activeTile))
        {
            activeTile->setYPos(activeTile->getYPos() + 1);
        }
        else
        {
            int rows = board->updateBoard(activeTile);
            if (rows > 0)
            {
                calculateScore(rows);

                QString scoreText = QStringLiteral("Score: %1").arg(score);
                ui->scoreLabel->setText(scoreText);

                if (rowDeletedSound->state() == QMediaPlayer::PlayingState && isGameSounds)
                {
                    rowDeletedSound->setPosition(0);
                }
                else if ((rowDeletedSound->state() == QMediaPlayer::PausedState || rowDeletedSound->state() == QMediaPlayer::StoppedState) && isGameSounds)
                {
                    rowDeletedSound->play();
                }
            }
            holdTileGen = false;
            delete ghostTile;
            delete activeTile;
            activeTile = nextTile;
            ghostTile = nextGhostTile;
            nextTile = chooseNextTile();
            nextTileScene->clear();
            drawNextTile();
        }
        updateView();
        if(isSoftDrop && gameInterval > SOFT_DROP_SPEED)
        {
            timer->start(SOFT_DROP_SPEED);
        }
        else
        {
            timer->start(gameInterval);
        }
    }
    else
    {
        ui->restartButton->setVisible(false);
        ui->playButton->setFocus();
        isPlaying = false;
        isGameOver = true;
        backgroundMusic->stop();
        if(isGameSounds)
            gameOverSound->play();
        drawGameOver();
        timer->stop();
        ui->playButton->setText("Restart");
    }
}

void GameController::switchHoldTile()
{
    holdTileGen = true;
    Tile * tempTile = activeTile;
    if(holdTile != NULL)
        activeTile = holdTile;
    else
    {
        delete ghostTile;
        activeTile = nextTile;
        ghostTile = nextGhostTile;
        nextTile = chooseNextTile();
        nextTileScene->clear();
        drawNextTile();
    }
    holdTileScene->clear();
    holdTile = tempTile;
    holdTile->setYPos(0);
    holdTile->setXPos(4);
    drawHoldTile(holdTile);
}


void GameController::updateView()
{
    ui->board->setFocus();
    ghostTile->setXPos(activeTile->getXPos());
    ghostTile->setShape(activeTile->getShape());
    boardScene->clear();
    drawBoard();
    drawActiveTileOnBoard();
    drawGhostTile();
}

void GameController::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        isSoftDrop = false;
    }
}

void GameController::keyPressEvent(QKeyEvent * event)
{
    if(!isPlaying && event->key() == Qt::Key_P)
    {
        handleGame();
        return;
    }
    if(!isPlaying)
    {
        return;
    }
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        if (board->isHorizontalMoveValid(activeTile, 1))
        {
            activeTile->setXPos(activeTile->getXPos() + 1);
        }
    }
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        if (board->isHorizontalMoveValid(activeTile, -1))
        {
            activeTile->setXPos(activeTile->getXPos() - 1);
        }
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        if(!isSoftDrop) generation();
        isSoftDrop = true;
    }
    else if (event->key() == Qt::Key_P)
    {
        handleGame();
    }
    else if (event->key() == Qt::Key_Space)
    {
        // set tile on the lowest possible y pos
        board->slamTile(activeTile);
        generation();
        if (slamTileSound->state() == QMediaPlayer::PlayingState && isGameSounds)
        {
            slamTileSound->setPosition(0);
        }
        else if ((slamTileSound->state() == QMediaPlayer::PausedState || slamTileSound->state() == QMediaPlayer::StoppedState) && isGameSounds)
        {
            slamTileSound->play();
        }
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        if (board->isRotationValid(activeTile))
        {
            activeTile->rotate();

            if (rotateSound->state() == QMediaPlayer::PlayingState && isGameSounds)
            {
                rotateSound->setPosition(0);
            }
            else if ((rotateSound->state() == QMediaPlayer::PausedState || rotateSound->state() == QMediaPlayer::StoppedState) && isGameSounds)
            {
                rotateSound->play();
            }
        }
    }
    else if (event->key() == Qt::Key_C)
    {
        if (!holdTileGen) //Checks to see if switchHoldTile was pressed once this "round"
            switchHoldTile();
    }
    updateView();
}

void GameController::calculateScore(int rows){
    int genScore;
    switch (rows) {
    case 1:
        genScore = 40;
        break;
    case 2:
        genScore = 100;
        break;
    case 3:
        genScore = 300;
        break;
    case 4:
        genScore = 1200;
        break;
    default:
        genScore = 0;
        break;
    }
    score += (level)*genScore;
    rowsCompleted += rows;

    if(rowsCompleted >= 10)
    {
        level++;
        gameInterval = (pow(0.8-((level-1)*0.007), ((level-1)))*1000);
        rowsCompleted = rowsCompleted - 10;

        // Update score text in GUI
        QString levelText = QStringLiteral("Level: %1").arg(level);
        ui->levelLabel->setText(levelText);
    }

}

void GameController::saveHighscore()
{
    if (score > highScore)
    {
        saveGameScore(playername, score);
        highScore = score;
    }
}

void GameController::setSettings(bool isBackgroundMusic, bool isGameSounds, string playername)
{
    this->isBackgroundMusic = isBackgroundMusic;
    this->isGameSounds = isGameSounds;
    this->playername = playername;
}

void GameController::setHighscore(int highscore)
{
    this->highScore = highscore;
    QString highscoreText = QStringLiteral("Highscore: %1").arg(highScore);
    ui->highscoreLabel->setText(highscoreText);
}

void GameController::handleMenuSettings()
{
    if(isPlaying)
        handleGame();
    emit gameClosed();
    this->close();

}

GameController::~GameController()
{
    saveHighscore();
}
