#ifndef _VECTORS_HPP_
#define _VECTORS_HPP_

#include <cmath>

class Vector
{
    public:
        Vector(const double x, const double y);
        ~Vector();

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_length() const { return sqrt(x_ * x_ + y_ * y_); }

        Vector normalize() const;

        Vector operator=(const Vector& second);

        void print() const;

    private:
        double x_, y_;
};
typedef Vector Dot;

Vector operator-(const Vector& self);
Vector operator-(const Vector& self, const Vector& second);
Vector operator+(const Vector& self, const Vector& second);
Vector operator*(const Vector& self, const double scalar);
Vector operator/(const Vector& self, const double scalar);

static const Vector NAN_VECTOR = {NAN, NAN};

Vector reflect_vector(const Vector& falling, const Vector& normal);
double cosinus(const Vector& first, const Vector& second);

#endif // _VECTORS_HPP_
