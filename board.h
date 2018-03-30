#ifndef BOARD_H
#define BOARD_H
#import "tile.h"
#include <vector>

using namespace std;

class Board
{
public:
    //Size of the board.
    static const int ROWS = 20;
    static const int COLS = 10;


    Board();
    ~Board();

    //Member functions to be implemented
    int updateBoard(Tile * tile);
    bool isHorizontalMoveValid(Tile * tile, int direction);
    bool isVerticalMoveValid(Tile * tile);
    bool isRotationValid(Tile * tile);             //TODO: fix member function. It is not properly working yet

    //Getters and setters
    vector<vector<int>> getBoard();

private:
    //The board is created like this: [ROWS][COLS]
    //Which means that ROWS is always the first loop
    vector<vector<int>> board;

    bool isGameOver();
    bool setTileOnBoard(Tile * tile);
    vector<int> checkFullRows(Tile * tile);
    void deleteRows(vector<int> rowNumbers);
};

#endif // BOARD_H