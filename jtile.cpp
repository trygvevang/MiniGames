#include "jtile.h"

JTile::JTile()
{
    vector<vector<int>> shape = {
        {2, 2, 2},
        {0, 0, 2}
    };

    Point center(0, 1);
    setShape(shape);
    setCenterPoint(center);
}
void JTile::rotate()
{
    Tile::rotate();
    vector<vector<int>> rotatedShape = getShape();

    //TODO: check if position is correct
    if (rotatedShape.size() == 3)
    {
        if (rotatedShape[0][0] != 0)
        {
            // CENTER_POINT = (1,0)
            setCenterPoint(Point(1,0));
        }
        else
        {
            // CENTER_POINT = (1,1)
            setCenterPoint(Point(1,1));
        }
    }
    else
    {
        if (rotatedShape[1][0] != 0)
        {
            // CENTER_POINT = (0,1)
            setCenterPoint(Point(1,1));
        }
        else
        {
            // CENTER_POINT = (1,1)
            setCenterPoint(Point(0,1));
        }
    }
}

JTile::~JTile()
{

}
