#ifndef LTILE_H
#define LTILE_H
#include "tile.h"
#include "vector"

using namespace std;

class LTile : public Tile
{
public:
    LTile();
    ~LTile();
    virtual void rotate();
};

#endif // LTILE_H
