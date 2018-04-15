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

Tile::Tile()
{
    // Start position is first row, sixth column
    Point point(0, 5);
    position = point;
}

/*
    Calls getRotatedShape() whichs returns shape of tile rotated clockwise 90 degrees,
    and set the shape to it. Member function is only to be called if rotaion is valid.
*/
void Tile::rotate()
{ 
    setShape(getRotatedShape());
}

Point Tile::getCenterPoint()
{
    return CENTER_POINT;
}

void Tile::setCenterPoint(Point center)
{
    CENTER_POINT = center;
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

vector<vector<int>> Tile::getShape() const
{
    return shape;
}

vector<vector<int>> Tile::getRotatedShape() const
{
    vector<vector<int>> shape = getShape();
    vector<vector<int>> rotatedShape (0);

    // Rotated shape has as many rows as there are columns in shape
    for (unsigned int i = 0; i < shape[0].size(); i++)
    {
        rotatedShape.push_back({});
    }

    // Rotate clockwise 90 degrees
    for (int i = shape.size() - 1; i >= 0; i--)
    {
        for (unsigned int j = 0; j < shape[0].size(); j++)
        {
            rotatedShape[j].push_back(shape[i][j]);
        }
    }
    return rotatedShape;
}

void Tile::setShape(vector<vector<int>> shape)
{
    this->shape = shape;
}

Tile::~Tile()
{

}

