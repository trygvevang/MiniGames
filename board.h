#ifndef BOARD_H
#define BOARD_H

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
    int updateBoard();                  //TODO: import Tile.h and pass in as param
    bool isHorizontalMoveValid();       //TODO: import Tile.h and pass in as param
    bool isVerticalMoveValid();         //TODO: import Tile.h and pass in as param
    bool isRotationValid();             //TODO: import Tile.h and pass in as param

    //Getters and setters
    vector<vector<int>> getBoard();

private:
    //The board is created like this: [ROWS][COLS]
    //Which means that ROWS is always the first loop
    vector<vector<int>> board;

    bool isGameOver();
    bool setTileOnBoard();              //TODO: import Tile.h and pass in as param
    vector<int> checkFullRows();        //TODO: param should be int row(?)
    void deleteRows(vector<int> rowNumbers);
};

#endif // BOARD_H
