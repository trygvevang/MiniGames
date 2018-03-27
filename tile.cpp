#include "tile.h"

/*
    Define member functions of struct Point
*/
int& Point::getX()
{
    return x;
}

int& Point::getY()
{
    return y;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}


/*
    Define non-abstract member functions of class Tile
*/
Point Tile::getCenterPoint()
{
    return CENTER_POINT;
}

int Tile::getXPos()
{
    return position.getX();
}

int Tile::getYPos()
{
    return position.getY();
}

void Tile::setXPos(int row)
{
    position.setX(row);
}

void Tile::setYPos(int column)
{
    position.setY(column);
}

vector<vector<int>> Tile::getShape()
{
    return shape;
}

void Tile::setShape(vector<vector<int>> shape)
{
    this->shape = shape;
}

Tile::~Tile()
{

}

