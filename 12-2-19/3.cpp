#include <iostream>

class Vector{
    private:
        int module;
        float angle;
    public:
        void set_module(int);
        void set_angle(float);

        int get_module();
        float get_angle();

        Vector operator+(const Vector& other); 
        Vector operator++(); //Preincremento
        Vector& operator++(int); //Postincremento
        friend std::ostream& operator<<(std::ostream& stream,const Vector& vect);
        friend std::istream& operator>>(std::istream& stream, Vector& vect);
        operator int();
};