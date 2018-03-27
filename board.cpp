#include "board.h"
#include <vector>

using namespace std;


//Constructor
Board::Board()
{
    //TODO: find a better way to initialize the vector
    this->board.resize(ROWS);
    for(unsigned r = 0; r < this->board.size(); r++){
        this->board[r].resize(COLS);
    }
}


//Private helper methods
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

vector<int> Board::checkFullRows()
{
    bool isRowFull;
    vector<int> fullRows;
    for(unsigned int r = 0; r < this->board.size(); r++){
        isRowFull = true;
        for (unsigned int c = 0; c < this->board[r].size(); c++) {
            if (c == 0) {
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
