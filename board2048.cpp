#include "board2048.h"

Board2048::Board2048()
{
    board.resize(BOARD_SIZE);
    for(unsigned r = 0; r < board.size(); r++){
        board[r].resize(BOARD_SIZE);
    }
}

void Board2048::spawnTile()
{
    rand = QRandomGenerator::securelySeeded();
    bool isSpawned = false;
    int randomRow, randomCol, randomDigit;
    while(!isSpawned){
        randomRow = rand.operator ()() % BOARD_SIZE;
        randomCol = rand.operator ()() % BOARD_SIZE;
        randomDigit = rand.operator ()() % 10;
        for(int r = 0; r < BOARD_SIZE; r++){
            for(int c = 0; c < BOARD_SIZE; c++){
                if(board[randomRow][randomCol] == 0)
                {
                    board[randomRow][randomCol] = randomDigit < 9 ? 2 : 4;
                    isSpawned = true;
                }
            }
        }
    }
}

vector<vector<int>> Board2048::getBoard()
{
    return board;
}


