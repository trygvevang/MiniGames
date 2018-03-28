#ifndef ITILE_H
#define ITILE_H
#include "tile.h"
#include "vector"

using namespace std;

class ITile : public Tile
{
public:
    ITile();
    ~ITile();
    virtual void rotate();
};

#endif // ITILE_H
