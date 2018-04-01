#include "gamecontroller.h"
#include <QDebug>
GameController::GameController(QWidget *parent) : QWidget(parent), ui(new Ui::Tetris)
{
    ui->setupUi(this);
    ui->graphicsView->setFocus();
    boardScene = new QGraphicsScene(this);
    nextTileScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(boardScene);
    ui->graphicsView_2->setScene(nextTileScene);

    boardScene->setSceneRect(0, 0, 300, 600);
    nextTileScene->setSceneRect(0, 0, 150, 150);

    ui->graphicsView->setSceneRect(boardScene->sceneRect());
    ui->graphicsView_2->setSceneRect(nextTileScene->sceneRect());
    initGame();

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(handleGame()));
    connect(timer, SIGNAL(timeout()), this, SLOT(generation()));
}

void GameController::drawNextTile()
{
    int boardLength = ui->graphicsView_2->width()/5;
    double middleOfWidth = ui->graphicsView_2->width()/8;
    double middleOfHeight = ui->graphicsView_2->height()/4;

    for (unsigned int i = 0; i < nextTile->getShape().size(); i++)
        {
            for (unsigned int j = 0; j < nextTile->getShape()[0].size(); j++)
            {
                if (nextTile->getShape()[i][j] != 0)
                {
                    QGraphicsRectItem * rect = new QGraphicsRectItem();
                    rect->setRect(j * boardLength + middleOfWidth, i * boardLength + middleOfHeight, boardLength, boardLength);

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
        color = "#ffff00";
        break;
    case 5:
        color = "#00ff00";
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
    random_device random;
    int randomIndex = random.operator ()() % 7; // mod number of different tiles

    if (randomIndex == 0)
    {
        ITile * iTile = new ITile();
        return iTile;
    }
    else if (randomIndex == 1)
    {
        JTile * jTile = new JTile();
        return jTile;
    }
    else if (randomIndex == 2)
    {
        LTile * lTile = new LTile();
        return lTile;
    }
    else if (randomIndex == 3)
    {
        OTile * oTile = new OTile();
        return oTile;
    }
    else if (randomIndex == 4)
    {
        STile * sTile = new STile();
        return sTile;
    }
    else if (randomIndex == 5)
    {
        TTile * tTile = new TTile();
        return tTile;
    }
    else
    {
        ZTile * zTile = new ZTile();
        return zTile;
    }
}

void GameController::initGame()
{
    activeTile = chooseNextTile();
    nextTile = chooseNextTile();
    board = new Board();
    timer = new QTimer(this);
    playlist = new QMediaPlaylist();
    player = new QMediaPlayer();

    playlist->addMedia(QUrl("qrc:/sounds/Sound/background-music.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);

    drawNextTile();
    drawBoard();
    drawActiveTileOnBoard();
}

void GameController::handleGame()
{
    if (!isPlaying)
    {
        timer->start(1000);
        isPlaying = true;
        ui->playButton->setText("Pause");
        if (ui->playGameMusic->isChecked())
            player->play();
    }
    else
    {
        timer->stop();
        isPlaying = false;
        ui->playButton->setText("Resume");
        player->pause();
    }
}

void GameController::generation()
{
    // Next genereation
    // TODO: Handle if game over
    if (board->isVerticalMoveValid(activeTile))
    {
        activeTile->setYPos(activeTile->getYPos() + 1);
    }
    else
    {
        board->updateBoard(activeTile);
        activeTile = nextTile;
        nextTile = chooseNextTile();
        nextTileScene->clear();
        drawNextTile();
    }
    updateView();
}

void GameController::parseProps()
{

}

void GameController::writeProps()
{

}


void GameController::updateView()
{
    boardScene->clear();
    drawBoard();
    drawActiveTileOnBoard();
}

void GameController::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        if (board->isHorizontalMoveValid(activeTile, 1))
            activeTile->setXPos(activeTile->getXPos() + 1);
    }
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        if (board->isHorizontalMoveValid(activeTile, -1))
            activeTile->setXPos(activeTile->getXPos() - 1);
    }
    else if (event->key() ==  Qt::Key_Down || event->key() == Qt::Key_S)
    {
        // set tile on the lowest possible y pos
    }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        if (board->isRotationValid(activeTile))
            activeTile->rotate();
    }
    updateView();
}

GameController::~GameController()
{

}
