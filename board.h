#ifndef BOARD_H
#define BOARD_H
#include "tile.h"
#include <vector>

using namespace std;

class Board
{
public:
    //Size of the board.
    static constexpr int ROWS = 20;
    static constexpr int COLS = 10;


    Board();
    ~Board();

    //Member functions to be implemented
    int updateBoard(Tile * tile);
    bool isHorizontalMoveValid(Tile * tile, int direction);
    bool isVerticalMoveValid(Tile * tile);
    bool isRotationValid(Tile * tile);
    void slamTile(Tile * tile);
    bool isGameOver(Tile * tile);

    //Getters and setters
    vector<vector<int>> getBoard();
private:
    //The board is created like this: [ROWS][COLS]
    //Which means that ROWS is always the first loop
    vector<vector<int>> board;


    bool setTileOnBoard(Tile * tile);
    vector<int> checkFullRows(Tile * tile);
    void deleteRows(vector<int> rowNumbers);
};

#endif // BOARD_H
