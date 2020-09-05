#include <iostream>

class Point{
    private:
        float x;
        float y;
    public:
        Point operator++();
        Point& operator++(int);
        Point operator-(const Point& other);
        friend std::istream& operator>>(std::istream &in, Point& p);
        friend std::ostream& operator<<(std::ostream &out, const Point& p);

        Point(Point &&other);
        Point& operator=(Point &&other);
        operator float() const;
};
