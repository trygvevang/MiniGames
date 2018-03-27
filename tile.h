#ifndef TILE_H
#define TILE_H
#include <vector>
#include <QGraphicsItem>
#include <QPoint>

using namespace std;
class Tile : public QGraphicsItem
{
public:
    Tile();
    virtual ~Tile();
    virtual vector<vector<int>> rotate();
    virtual vector<vector<int>> getShape();
    QPoint getCenterPoint();
    int getXPos();
    int getYPos();
    virtual void setShape();
    void setXPos(int row);
    void setYPos(int column);

private:
    vector<vector<int>> shape;
    QPoint * CENTER_POINT;
    int xPos;
    int yPos;
}

#endif // TILE_H
