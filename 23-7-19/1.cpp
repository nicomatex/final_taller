#include <iostream>

class Fraction{
    private:
        int numerator;
        int denominator;
    public:
        Fraction();
        Fraction(int numerator, int denominator);
        int get_numerator();
        int get_denominator();
        void set_numerator();
        void set_denominator();
        float get_fraction();
        operator float();

        Fraction operator+(const Fraction& other);
        Fraction& operator++(int);
        Fraction operator--();

        friend std::istream operator>>(std::istream& stream, Fraction& fraction);
        friend std::ostream operator<<(std::ostream& stream, const Fraction& fraction);


        operator long();
};