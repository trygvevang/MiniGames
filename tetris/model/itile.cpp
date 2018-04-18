#include "itile.h"

ITile::ITile() : Tile()
{
    vector<vector<int>> shape = {
        {1, 1, 1, 1}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}

void ITile::rotate()
{
    Tile::rotate();
}

ITile::~ITile()
{

}
