#ifndef BOARD2048_H
#define BOARD2048_H

#include <QRandomGenerator>
#include <vector>

using namespace std;

class Board2048
{
public:
    Board2048();

    bool isGameOver();
    int round(int direction); // 1 = left, 2 = down, 3 = right, 4 = up
    vector<vector<int>> getBoard();

    static constexpr int BOARD_SIZE = 4;

private:
    // [ROWS][COLS]
    vector<vector<int>> board;
    /*  Keeps track of what elements in board that do not have a value;
        index / 4 = row, index % 4 = column
        index = row * 4 + column
    */
    vector<int> availableIndexes;
    QRandomGenerator rand;

    int merge(int direction);
    bool move(int direction);
    void spawnTile();
    void updateAvailableIndexes();
    void removeIndexFromAvailable(int valueIndex);
    void addIndexToAvailable(int row, int column);
    bool isMergeable();
};

#endif // BOARD2048_H
