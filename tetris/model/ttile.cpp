#include "ttile.h"

TTile::TTile() : Tile()
{
    vector<vector<int>> shape = {
        {6, 6, 6},
        {0, 6, 0}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}

void TTile::rotate()
{
    Tile::rotate();
}


TTile::~TTile()
{

}
