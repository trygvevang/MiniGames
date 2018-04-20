#include "controller2048.h"
#include <QDebug>

Controller2048::Controller2048(QWidget *parent) : QWidget(parent), ui(new Ui::UI2048)
{
    board = new Board2048;
    ui->setupUi(this);
    ui->boardView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->boardView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->boardView->setFocus();
    boardScene = new QGraphicsScene(this);

    ui->boardView->setScene(boardScene);

    boardScene->setSceneRect(0,0,350,350);
    ui->boardView->setSceneRect(boardScene->sceneRect());

    connect(ui->backToMenuButton, SIGNAL(clicked()), this, SLOT(handleMenuSettings()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(handleRestart()));
    setupGame();
}

void Controller2048::setupGame()
{
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

void Controller2048::keyPressEvent(QKeyEvent * event)
{
    if (!board->isGameOver())
    {
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
    board->round(direction);
    drawBoard();
}
void Controller2048::handleRestart()
{

}

void Controller2048::handleMenuSettings()
{
    emit gameClosed();
    this->close();
}

Controller2048::~Controller2048()
{

}

