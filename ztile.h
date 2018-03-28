#ifndef ZTILE_H
#define ZTILE_H
#include "tile.h"
#include <vector>

using namespace std;

class ZTile : public Tile
{
public:
    ZTile();
    ~ZTile();
    virtual void rotate();
};

#endif // ZTILE_H
