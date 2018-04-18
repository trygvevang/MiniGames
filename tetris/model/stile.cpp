#include "stile.h"

STile::STile() : Tile()
{
    vector<vector<int>> shape = {
        {0, 5, 5},
        {5, 5, 0}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}

void STile::rotate()
{
    Tile::rotate();
}


STile::~STile()
{

}
