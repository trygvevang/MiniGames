#include "board.h"
#include <QDebug>

// Constructor
Board::Board()
{
    board.resize(ROWS);
    for(unsigned r = 0; r < board.size(); r++)
    {
        board[r].resize(COLS);
    }
}

// Public member functions
bool Board::isHorizontalMoveValid(Tile * tile, int direction) // if positive direction move right, else left
{
    int xPos;
    int yPos;
    vector<vector<int>> shape = tile->getShape();
    for(unsigned r = 0; r < shape.size(); r++)
    {
        for(unsigned c = 0; c < shape[r].size(); c++)
        {
            if(shape[r][c] != 0)
            {
                xPos = tile->getXPos() + c;
                yPos = tile->getYPos() + r;
                if(direction > 0)
                {
                    xPos++;
                }
                else
                {
                    xPos--;
                }

                if(xPos < 0 || xPos >= COLS || board[yPos][xPos] != 0)
                    return false;
            }
        }
    }
    return true;
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
    for(unsigned c = 0; c < shape[0].size(); c++)
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

void Board::slamTile(Tile * tile)
{
    while(isVerticalMoveValid(tile))
    {
        tile->setYPos(tile->getYPos() + 1);
    }
}

bool Board::isRotationValid(Tile * tile)
{
    vector<vector<int>> rotatedShape = tile->getRotatedShape();
    bool rotateInPlace = true;
    bool rotateRight = true;
    bool rotateLeft = true;
    for(int r = tile->getYPos(); r < tile->getYPos() + rotatedShape.size(); r++)
    {
        for(int c = tile->getXPos(); c < tile->getXPos() + rotatedShape[0].size(); c++)
        {
            if(r >= ROWS || c >= COLS || c < 0 || board[r][c] != 0){
                rotateInPlace = false;
            }
            if(r >= ROWS || c+1 >= COLS || board[r][c + 1] != 0){
                rotateRight = false;
            }
            if(r >= ROWS || c-1 < 0 || board[r][c-1] != 0){
                rotateLeft = false;
            }
        }
    }
    if(!rotateInPlace)
    {
        if(rotateRight)
        {
            tile->setXPos(tile->getXPos() + 1);
            return true;
        }
        else if(rotateLeft)
        {
            tile->setXPos(tile->getXPos() - 1);
            return true;
        }else
        {
            return false;
        }
    }
    return true;
}

int Board::updateBoard(Tile * tile)
{
    setTileOnBoard(tile);
    vector<int> fullRows = findFullRows(tile);
    deleteRows(fullRows);
    return fullRows.size();
}

bool Board::isGameOver(Tile * tile)
{
    int xPos;
    int yPos;
    for(unsigned c = 0; c < tile->getShape()[0].size(); c++)
    {
        for(int r = tile->getShape().size()-1; r >= 0; r--)
        {
            if (tile->getShape()[r][c] != 0)
            {
                yPos = tile->getYPos() + r;
                xPos = tile->getXPos() + c;
                if (board[yPos][xPos] != 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Private helper methods
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

vector<int> Board::findFullRows(Tile * tile)
{
    bool isRowFull;
    vector<int> fullRows;
    for(unsigned int r = tile->getYPos(); r < tile->getYPos() + tile->getShape().size(); r++){
        isRowFull = true;
        for (unsigned int c = 0; c < board[r].size(); c++)
        {
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
    for(unsigned int i = 0; i < rowNumbers.size(); i++)
    {
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
Board::~Board()
{
    this->board.clear();
    this->board.shrink_to_fit();
}
