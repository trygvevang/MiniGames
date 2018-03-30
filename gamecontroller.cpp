#include "gamecontroller.h"

GameController::GameController()
{
}

void GameController::drawNextTile()
{

}

void GameController::drawBoard()
{

}

Tile * GameController::chooseNextTile()
{
    random_device random;
    int randomIndex = random.operator ()() % 7; // mod number of different tiles
    Tile * tile;
    switch (randomIndex) {
    case 0:
    {
        ITile iTile;
        tile = &iTile;
        break;
    }
    case 1:
    {
        JTile jTile;
        tile = &jTile;
        break;
    }
    case 2:
    {
        LTile lTile;
        tile = &lTile;
        break;
    }
    case 3:
    {
        OTile oTile;
        tile = &oTile;
        break;
    }
    case 4:
    {
        STile sTile;
        tile = &sTile;
        break;
    }
    case 5:
    {
        TTile tTile;
        tile = &tTile;
        break;
    }
    default:
    {
        ZTile zTile;
        tile = &zTile;
        break;
    }
    }
    return tile;
}

void GameController::initGame()
{
    // resetBoard()
    activeTile = chooseNextTile();
    nextTile = chooseNextTile();
    // drawNextTile();
    // drawBoard();
    // init timer
}

void GameController::parseProps()
{

}

void GameController::writeProps()
{

}

void GameController::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_Right:
        if (board.isHorizontalMoveValid(activeTile, 1))
            activeTile->setXPos(activeTile->getXPos() + 1);
        drawBoard();
        break;
    case Qt::Key_Left:
        if (board.isHorizontalMoveValid(activeTile, -1))
            activeTile->setXPos(activeTile->getXPos() - 1);
        drawBoard();
        break;
    case Qt::Key_Down:
        // set tile on the lowest possible y pos
        drawBoard();
        break;
    case Qt::Key_Up:
        if (board.isRotationValid(activeTile))
            activeTile->rotate();
        drawBoard();
        break;
    default:
        break;
    }
}

GameController::~GameController()
{

}
