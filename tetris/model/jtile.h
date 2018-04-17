#ifndef JTILE_H
#define JTILE_H
#include "tile.h"
#include "vector"

using namespace std;

class JTile : public Tile
{
public:
    JTile();
    ~JTile();
    virtual void rotate();
};

#endif // JTILE_H
