#include "controller2048.h"

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
    int cellHeight = (ui->boardView->height())/board->BOARD_SIZE;
    int cellWidth = (ui->boardView->width())/board->BOARD_SIZE;

    for(int r = 0; r < board->BOARD_SIZE; r++){
        for(int c = 0; c < board->BOARD_SIZE; c++){
            QGraphicsRectItem * rect = new QGraphicsRectItem();
            rect->setRect(c*cellWidth, r*cellHeight, cellWidth, cellHeight);
            if(board->getBoard()[r][c] != 0){
                QBrush brush(Qt::SolidPattern);
                const QColor color(100,100,100, 255);
                brush.setColor(color);
                rect->setBrush(brush);
            }
            boardScene->addItem(rect);
        }
    }
}

void Controller2048::keyPressEvent(QKeyEvent * event)
{

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

