#include "otile.h"

OTile::OTile() : Tile()
{
    vector<vector<int>> shape = {
        {4, 4},
        {4, 4}
    };

    Point center(0, 0);
    setShape(shape);
    setCenterPoint(center);
    setXPos(getXPos() - 1);
}

void OTile::rotate()
{
    // OTile does not rotate
}


OTile::~OTile()
{

}
