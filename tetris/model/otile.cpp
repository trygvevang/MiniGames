#include "otile.h"

OTile::OTile() : Tile()
{
    vector<vector<int>> shape = {
        {4, 4},
        {4, 4}
    };

    setShape(shape);
    setXPos(getXPos() - 1);
}

void OTile::rotate()
{
    // OTile does not rotate
}


OTile::~OTile()
{

}
