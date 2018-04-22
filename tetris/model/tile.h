#ifndef TILE_H
#define TILE_H
#include <vector>

// Struct point defines position of a tile relative to the board
struct Point {
private:
    int y;
    int x;
public:
    Point(){}
    Point(int y, int x) : y(y), x(x)
    {}
    int& getY();
    int& getX();
    void setY(int y);
    void setX(int x);
};

using namespace std;
class Tile
{
public:
    Tile();
    virtual ~Tile();
    virtual void rotate() = 0; // Making Tile an abstract class
    virtual vector<vector<int>> getShape() const;
    vector<vector<int>> getRotatedShape() const;
    int getXPos();
    int getYPos();
    virtual void setShape(vector<vector<int>> shape);
    void setXPos(int row);
    void setYPos(int column);

private:
    vector<vector<int>> shape;
    Point position{}; // Position of tile on board
};

#endif // TILE_H
