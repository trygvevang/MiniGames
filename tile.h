#ifndef TILE_H
#define TILE_H
#include <vector>
#include <QGraphicsItem>

struct Point {
private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y)
    {}
    int& getX();
    int& getY();
    void setX(int x);
    void setY(int y);
};

using namespace std;
class Tile : public QGraphicsItem
{
public:
    Tile();
    virtual ~Tile();
    virtual vector<vector<int>> rotate() = 0;
    virtual vector<vector<int>> getShape();
    Point getCenterPoint();
    int getXPos();
    int getYPos();
    virtual void setShape(vector<vector<int>> shape);
    void setXPos(int row);
    void setYPos(int column);

private:
    vector<vector<int>> shape;
    Point CENTER_POINT; // Center point on tile. Determines what point rotation is to revolve around.
    Point position; // Position of tile on board
};

#endif // TILE_H
