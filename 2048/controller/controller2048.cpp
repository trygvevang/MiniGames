#include "controller2048.h"
#include <cmath>

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

unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

void Controller2048::keyPressEvent(QKeyEvent * event)
{
    if (!board->isGameOver())
    {
        // 1 = left, 2 = down, 3 = right, 4 = up
        if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        {
            board->round(1);
        }
        else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        {
            board->round(2);
        }
        else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        {
            board->round(3);
        }
        else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        {
            board->round(4);
        }
        drawBoard();
    }
}

void Controller2048::handleRestart()
{

}

void Controller2048::handleMenuSettings()
{
    emit gameClosed();
    this->close();
}

QString Controller2048::setRectColor(int value)
{
    QString color;
    switch (value)
    {
    case 2:
        color = "#00ffff";
        break;
    case 4:
        color = "#0000ff";
        break;
    case 8:
        color = "#ffa500";
        break;
    case 16:
        color = "#FFF504";
        break;
    case 32:
        color = "#00D11B";
        break;
    case 64:
        color = "#551A8B";
        break;
    default:
        color = "#ff0000";
        break;
    }
    return color;
}

Controller2048::~Controller2048()
{

}

