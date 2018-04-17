#ifndef OTILE_H
#define OTILE_H
#include "tile.h"
#include "vector"

using namespace std;

class OTile : public Tile
{
public:
    OTile();
    ~OTile();
    virtual void rotate();
};

#endif // OTILE_H
