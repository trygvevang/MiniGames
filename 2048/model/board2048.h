#ifndef BOARD2048_H
#define BOARD2048_H

#include <QRandomGenerator>
#include <vector>

using namespace std;

class Board2048
{
public:
    Board2048();

    void spawnTile();
    vector<vector<int>> getBoard();

    static constexpr int BOARD_SIZE = 4;

private:
    // [ROWS][COLS]
    vector<vector<int>> board;
    QRandomGenerator rand;

};

#endif // BOARD2048_H
