#include "board2048.h"
#include <QDebug>
Board2048::Board2048()
{
    // Generate a board with BOARD_SIZE * BOARD_SIZE number of elements
    board.resize(BOARD_SIZE);
    for(unsigned r = 0; r < board.size(); r++){
        board[r].resize(BOARD_SIZE);
    }

    // Every index up to BOARD_SIZE * BOARD_SIZE is available indexes initially
    for (unsigned index = 0; index < BOARD_SIZE * BOARD_SIZE; index++)
    {
        availableIndexes.push_back(index);
    }

    spawnTile();
    spawnTile();
}

bool Board2048::isGameOver()
{
    if(availableIndexes.size() > 0)
        return false;
    bool gameOver = !isMergeable();
    qDebug() << "Game over: " << gameOver;
    return !isMergeable();

}

bool Board2048::isMergeable()
{
    for(int r = 0; r < BOARD_SIZE - 1; r++)
    {
        for(int c = 0; c < BOARD_SIZE - 1; c++)
        {
            if(c+1 == 3)
                if(board[r+1][c+1] == board[r][c+1])
                    return true;

            if(r+1 == 3)
                if(board[r+1][c+1] == board[r+1][c])
                    return true;
            if(board[r][c] == board[r][c+1] || board[r][c] == board[r+1][c])
            {
                return true;
            }
        }
    }
    return false;
}

// If return true game is not over, else game over
int Board2048::round(int direction) // 1 = left, 2 = down, 3 = right, 4 = up
{
    if (!isGameOver())
    {
        int score = merge(direction);
        if(move(direction))
        {
            updateAvailableIndexes();
            spawnTile();

            return score > 1 ? score : 1;
        }
        return 0; // can not move any tiles
    }
    return -1; // if game over, return -1
}

vector<vector<int>> Board2048::getBoard()
{
    return board;
}

// Private member functions
int Board2048::merge(int direction)
{
    int score = 0;
    if (direction == 1) // Left
    {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board[row][col] != 0)
                {
                    // Check to see if have to merge
                    for (int colToCheck = col+1; colToCheck < BOARD_SIZE; colToCheck++)
                    {
                        if (board[row][colToCheck] == board[row][col])
                        {
                            board[row][colToCheck] *= 2;
                            score += board[row][colToCheck];
                            board[row][col] = 0;
                            col = colToCheck;
                            break;
                        }
                        else if (board[row][colToCheck] != 0)
                            break;
                    }
                }
            }
        }
    }
    else if(direction == 3) //Right
    {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = BOARD_SIZE-1; col >= 0; col--)
            {
                if (board[row][col] != 0)
                {
                    // Check to see if have to merge
                    for (int colToCheck = col - 1; colToCheck >= 0; colToCheck--)
                    {
                        if (board[row][colToCheck] == board[row][col])
                        {
                            board[row][colToCheck] *= 2;
                            score += board[row][colToCheck];
                            board[row][col] = 0;
                            col = colToCheck;
                            break;
                        }
                        else if (board[row][colToCheck] != 0)
                            break;
                    }
                }
            }
        }
    }
    else if(direction == 2) // Down
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            for (int row = BOARD_SIZE - 1; row >= 0; row--)
            {
                if (board[row][col] != 0)
                {
                    // Check to see if have to merge
                    for (int rowToCheck = row - 1; rowToCheck >= 0; rowToCheck--)
                    {
                        if (board[rowToCheck][col] == board[row][col])
                        {
                            board[rowToCheck][col] *= 2;
                            score += board[rowToCheck][col];
                            board[row][col] = 0;
                            row = rowToCheck;
                            break;
                        }
                        else if (board[rowToCheck][col] != 0)
                            break;
                    }
                }
            }
        }
    }
    else if(direction == 4) // Up
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
                for (int row = 0; row < BOARD_SIZE; row++)
            {
                if (board[row][col] != 0)
                {
                    // Check to see if have to merge
                    for (int rowToCheck = row + 1; rowToCheck < BOARD_SIZE; rowToCheck++)
                    {
                        if (board[rowToCheck][col] == board[row][col])
                        {
                            board[rowToCheck][col] *= 2;
                            score += board[rowToCheck][col];
                            board[row][col] = 0;
                            row = rowToCheck;
                            break;
                        }
                        else if (board[rowToCheck][col] != 0)
                            break;
                    }
                }
            }
        }
    }
    return score;
}

bool Board2048::move(int direction)
{
    bool moved = false;
    switch (direction) {
    case 1:
        // Move left
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board[row][col] != 0)
                {
                    for (int colToCheck = col - 1; colToCheck >= 0; colToCheck--)
                    {
                        if (board[row][colToCheck] != 0)
                        {
                            int temp = board[row][col];
                            board[row][col] = 0;
                            board[row][colToCheck + 1] = temp;
                            if (colToCheck+1 != col)
                                moved = true;
                            break;
                        }
                        else if (colToCheck == 0 && board[row][colToCheck] == 0)
                        {
                            board[row][colToCheck] = board[row][col];
                            board[row][col] = 0;
                            moved = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case 2:
        // Move down
        for (int row = BOARD_SIZE - 1; row >= 0; row--)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board[row][col] != 0)
                {
                    for (int rowToCheck = row + 1; rowToCheck < BOARD_SIZE; rowToCheck++)
                    {
                        if (board[rowToCheck][col] != 0)
                        {
                            int temp = board[row][col];
                            board[row][col] = 0;
                            board[rowToCheck - 1][col] = temp;
                            if(rowToCheck-1 != row)
                                moved = true;
                            break;
                        }
                        else if (rowToCheck == BOARD_SIZE - 1 && board[rowToCheck][col] == 0)
                        {
                            board[rowToCheck][col] = board[row][col];
                            board[row][col] = 0;
                            moved = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case 3:
        // Move right
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = BOARD_SIZE - 1; col >= 0; col--)
            {
                if (board[row][col] != 0)
                {
                    for (int colToCheck = col + 1; colToCheck < BOARD_SIZE; colToCheck++)
                    {
                        if (board[row][colToCheck] != 0)
                        {
                            int temp = board[row][col];
                            board[row][col] = 0;
                            board[row][colToCheck - 1] = temp;
                            if (colToCheck-1 != col)
                                moved = true;
                            break;
                        }
                        else if (colToCheck == BOARD_SIZE - 1 && board[row][colToCheck] == 0)
                        {
                            board[row][colToCheck] = board[row][col];
                            board[row][col] = 0;
                            moved = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
    default:
        // Move up
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board[row][col] != 0)
                {
                    for (int rowToCheck = row - 1; rowToCheck >= 0; rowToCheck--)
                    {
                        if (board[rowToCheck][col] != 0)
                        {
                            int temp = board[row][col];
                            board[row][col] = 0;
                            board[rowToCheck + 1][col] = temp;
                            if(rowToCheck+1 != row)
                                moved = true;
                            break;
                        }
                        else if (rowToCheck == 0 && board[rowToCheck][col] == 0)
                        {
                            board[rowToCheck][col] = board[row][col];
                            board[row][col] = 0;
                            moved = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
    return moved;
}

void Board2048::updateAvailableIndexes()
{
    vector<int> updatedAvailable;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (board[row][col] == 0)
            {
                int index = row * 4 + col;
                updatedAvailable.push_back(index);
            }
        }
    }
    availableIndexes = updatedAvailable;
}

void Board2048::spawnTile()
{
    rand = QRandomGenerator::securelySeeded();
    int index = (rand.operator ()() % availableIndexes.size());
    int randomIndex = availableIndexes[index];
    int probability = (rand.operator ()() % 100);
    int randomValue = probability >= 90 ? 4 : 2; // There is a 10 % probability of the tile spawning being 4
    int row = randomIndex / BOARD_SIZE;
    int column = randomIndex % BOARD_SIZE;

    board[row][column] = randomValue;
    removeIndexFromAvailable(randomIndex);
}

void Board2048::removeIndexFromAvailable(int valueIndex)
{
    //int valueIndex = row * 4 + column;
    vector<int>::iterator position = find(availableIndexes.begin(), availableIndexes.end(), valueIndex);
    if (position != availableIndexes.end())
        availableIndexes.erase(position);
}

void Board2048::addIndexToAvailable(int row, int column)
{
    int valueIndex = row * 4 + column;
    availableIndexes.push_back(valueIndex);
}
