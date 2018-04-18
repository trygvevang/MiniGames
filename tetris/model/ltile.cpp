#include "ltile.h"

LTile::LTile() : Tile()
{
    vector<vector<int>> shape = {
        {0, 0, 3},
        {3, 3, 3}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}

void LTile::rotate()
{
    Tile::rotate();
}

LTile::~LTile()
{

}
