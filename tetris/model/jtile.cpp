#include "jtile.h"

JTile::JTile() : Tile()
{
    vector<vector<int>> shape = {
        {2, 2, 2},
        {0, 0, 2}
    };

    setShape(shape);
    setXPos(getXPos() - 2);
}
void JTile::rotate()
{
    Tile::rotate();
}

JTile::~JTile()
{

}
