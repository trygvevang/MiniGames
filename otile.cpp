#include "otile.h"

OTile::OTile()
{
    vector<vector<int>> shape = {
        {1, 1},
        {1, 1}
    };

    Point center(0, 0);
    setShape(shape);
    setCenterPoint(center);
}

void OTile::rotate()
{
    // OTile does not rotate
}

OTile::~OTile()
{

}
