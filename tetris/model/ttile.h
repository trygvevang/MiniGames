#ifndef TTILE_H
#define TTILE_H
#include "tile.h"
#include <vector>

using namespace std;

class TTile : public Tile
{
public:
    TTile();
    ~TTile();
    virtual void rotate();
};

#endif // TTILE_H
