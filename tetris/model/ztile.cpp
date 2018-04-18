#include "ztile.h"

ZTile::ZTile() : Tile()
{
    vector<vector<int>> shape = {
        {7, 7, 0},
        {0, 7, 7}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}

void ZTile::rotate()
{
    Tile::rotate();
}

ZTile::~ZTile()
{

}
