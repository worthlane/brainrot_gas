#include <cmath>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include "maths/vectors.hpp"

static bool is_zero(const double num);

static const double EPSILON = 1e-9;

// ================================================================

Vector::Vector(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

// ----------------------------------------------------------------------

Vector::~Vector()
{
    x_ = NAN;
    y_ = NAN;
}

// ----------------------------------------------------------------------

Vector Vector::operator=(const Vector& second)
{
    x_ = second.x_;
    y_ = second.y_;

    return *this;
}

// ----------------------------------------------------------------------

Vector operator-(const Vector& self)
{
    return {-self.get_x(), -self.get_y()};
}

// ----------------------------------------------------------------------

Vector operator+(const Vector& self, const Vector& second)
{
    Vector result = {  self.get_x() + second.get_x(),
                        self.get_y() + second.get_y() };

    return result;
}

// ----------------------------------------------------------------------

Vector operator-(const Vector& self, const Vector& second)
{
    Vector result = {  self.get_x() - second.get_x(),
                        self.get_y() - second.get_y() };

    return result;
}

// ----------------------------------------------------------------------

Vector Vector::normalize() const
{
    double len = this->get_length();

    Vector result = {x_ / len, y_ / len};

    return result;
}


// ----------------------------------------------------------------------

Vector operator*(const Vector& self, const double scalar)
{
    Vector result = {  self.get_x() * scalar,
                        self.get_y() * scalar };

    return result;
}

// ----------------------------------------------------------------------

Vector operator/(const Vector& self, const double scalar)
{
    Vector result = {  self.get_x() / scalar,
                        self.get_y() / scalar };

    return result;
}

// ----------------------------------------------------------------------

void Vector::print() const
{
    Vector vec = *this;

    printf("%g %g\n", vec.x_, vec.y_);
}

// ----------------------------------------------------------------------

static bool is_zero(const double num)
{
    double diff = fabs(num);

    return (diff < EPSILON) ? true : false;
}

// ----------------------------------------------------------------------

double cosinus(const Vector& first, const Vector& second)
{
    Vector third_edge = first - second;

    double a = first.get_length();
    double b = second.get_length();
    double c = third_edge.get_length();

    double cos = (a * a + b * b - c * c) / (2 * a * b);

    return cos;
}

// ----------------------------------------------------------------------

Vector reflect_vector(const Vector& falling, const Vector& normal)
{
    Vector normalized = normal.normalize();

    Vector reflected = falling - normalized * (2 * (falling * normalized));

    return reflected;
}

// ----------------------------------------------------------------------

bool directed_towards(const Vector& first, const Vector& second)
{
    double cos = cosinus(first, second);

    return (cos > 0) ? true : false;
}

// ----------------------------------------------------------------------

double operator*(const Vector& self, const Vector& other)
{
    return self.get_x() * other.get_x() + self.get_y() * other.get_y();
}

// ----------------------------------------------------------------------

CompareResult compare_double(const double first, const double second)
{
    static const double EPSILON = 1e-6;

    double diff = first - second;

    if (fabs(diff) < EPSILON)
        return CompareResult::EQUAL;
    else if (diff < -EPSILON)
        return CompareResult::LESS;
    else
        return CompareResult::GREATER;
}

