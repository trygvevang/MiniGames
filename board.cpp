#include "board.h"
#include <QDebug>

// Constructor
Board::Board()
{
    board.resize(ROWS);
    for(unsigned r = 0; r < board.size(); r++){
        board[r].resize(COLS);
    }
}

// Public member functions
bool Board::isHorizontalMoveValid(Tile * tile, int direction) // if positive direction move right, else left
{
    int yPos = tile->getYPos();
    int xPosToCheck = direction > 0 ? tile->getXPos() + tile->getShape()[0].size() : tile->getXPos() - 1;
    if (xPosToCheck < COLS && xPosToCheck >= 0) // Check if next X-position is valid on the board
    {
        for (unsigned int i = yPos; i < yPos + tile->getShape().size(); i++)
        {
            if (board[i][xPosToCheck] != 0)
            {return false;}
        }
        return true;
    }
    return false;
}
bool Board::isVerticalMoveValid(Tile * tile)
{
    vector<vector<int>> shape = tile->getShape();
    int lowestYToCheck = tile->getYPos() + shape.size();
    if (lowestYToCheck >= ROWS)
    {
        return false;
    }
    int xPos;
    int yPos;
    bool isValid = true;
    for(int c = 0; c < shape[0].size(); c++)
    {
        for(int a = shape.size()-1; a >= 0; a--)
        {
            if (shape[a][c] != 0)
            {
                yPos = tile->getYPos() + a;
                xPos = tile->getXPos() + c;
                if (board[yPos+1][xPos] != 0)
                {
                    isValid = false;
                    break;
                }
            }
        }
    }
    return isValid;
}

void Board::quickPlace(Tile * tile){
    while(isVerticalMoveValid(tile)){
        tile->setYPos(tile->getYPos() + 1);
    }
}


// This method will not work yet. If tile is on edge of board and rotates, what then?
bool Board::isRotationValid(Tile * tile)
{
    vector<vector<int>> rotatedShape = tile->getRotatedShape();
    for (unsigned int i = tile->getYPos(); i < tile->getYPos() + rotatedShape.size(); i++)
    {
        for (unsigned int j = tile->getXPos(); j < tile->getXPos() + rotatedShape[0].size(); j++)
        {
            if (board[i][j] != 0)
            {return false;}
        }
    }

    return true;
}

int Board::updateBoard(Tile * tile)
{
    setTileOnBoard(tile);
    vector<int> fullRows = checkFullRows(tile);
    deleteRows(fullRows);
    switch (fullRows.size()) {
    case 0:
        return 0;
    case 1:
        return 40;
    case 2:
        return 100;
    case 3:
        return 300;
    case 4:
        return 1200;
    default:
        return 0;
    }
}

// Private helper methods
bool Board::isGameOver()
{
    for(unsigned int r = 0; r < this->board.size(); r++) {
        for (unsigned int c = 0; c < this->board[r].size();c++) {
            if (this->board[r][c] >= 1 && this->board[r+1][c] < 1) { //TODO: probably too basic condition
                return false;
            }
        }
    }
    return true;
}

bool Board::setTileOnBoard(Tile * tile)
{
    for (unsigned int r = 0; r < tile->getShape().size(); r++)
    {
        for (unsigned int c = 0; c < tile->getShape()[0].size(); c++)
        {
            // Should there be any check on value of baord?
            if(tile->getShape()[r][c] == 0) continue;
            board[r + tile->getYPos()][c + tile->getXPos()] = tile->getShape()[r][c];
        }
    }
    return true;
}

vector<int> Board::checkFullRows(Tile * tile)
{
    bool isRowFull;
    vector<int> fullRows;
    for(unsigned int r = tile->getYPos(); r < tile->getYPos() + tile->getShape().size(); r++){
        isRowFull = true;
        for (unsigned int c = 0; c < board[r].size(); c++) {
            if (board[r][c] == 0) {
                isRowFull = false;
            }
        }
        if (isRowFull) {
            fullRows.push_back(r);
        }
    }
    return fullRows;
}

void Board::deleteRows(vector<int> rowNumbers)
{
    for(unsigned int i = 0; i < rowNumbers.size(); i++){
        unsigned rowToDelete = rowNumbers[i];
        if (board.size() > rowToDelete)
        {
            board.erase(board.begin() + rowToDelete );
        }
        board.insert(board.begin(),vector<int>(Board::COLS,0));
    }
}

//Getters
vector<vector<int>> Board::getBoard(){
    return this->board;
}


//Destructor
Board::~Board(){
    this->board.clear();
    this->board.shrink_to_fit();
}
