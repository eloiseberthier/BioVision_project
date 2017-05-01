#pragma once
#include <list>

namespace psc_utils
{

class Point
{
private:
    int x; // this fields are protected
    int y;
public:
    Point(int X, int Y);
    Point();

    ~Point();

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    int getY() const;
    int getX() const;
    std::list<Point> voisins(int r, int largest_x, int largest_y);

};

}
