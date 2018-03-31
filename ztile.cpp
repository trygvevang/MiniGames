#include "ztile.h"

ZTile::ZTile() : Tile()
{
    vector<vector<int>> shape = {
        {7, 7, 0},
        {0, 7, 7}
    };

    Point center(0, 1);
    setShape(shape);
    setCenterPoint(center);
    setXPos(getXPos() - 2);
}

void ZTile::rotate()
{
    Tile::rotate();
    vector<vector<int>> rotatedShape = getShape();

    //TODO: check if position is correct
    if (rotatedShape.size() == 3)
    {
        //CENTER_POINT = (1,1)
        setCenterPoint(Point(1,1));
    }
    else
    {
        // CENTER_POINT = (0,1)
        setCenterPoint(Point(0,1));
    }
}

ZTile::~ZTile()
{

}
