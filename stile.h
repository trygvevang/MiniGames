#ifndef STILE_H
#define STILE_H
#include "tile.h"
#include "vector"

using namespace std;

class STile : public Tile
{
public:
    STile();
    ~STile();
    virtual void rotate();
};

#endif // STILE_H
