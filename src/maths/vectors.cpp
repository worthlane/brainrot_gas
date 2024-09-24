#include <cmath>
#include <stdio.h>
#include <assert.h>

#include "maths/vectors.hpp"

static bool is_zero(const double num);

static const double EPSILON = 1e-9;

// ================================================================

Vector2::Vector2(const double x, const double y)
{
    x_ = x;
    y_ = y;
}

// ----------------------------------------------------------------------

Vector2::~Vector2()
{
    x_ = NAN;
    y_ = NAN;
}

// ----------------------------------------------------------------------

Vector2 Vector2::operator=(const Vector2& second)
{
    x_ = second.x_;
    y_ = second.y_;

    return *this;
}

// ----------------------------------------------------------------------

Vector2 operator-(const Vector2& self)
{
    return {-self.get_x(), -self.get_y()};
}

// ----------------------------------------------------------------------

Vector2 operator+(const Vector2& self, const Vector2& second)
{
    Vector2 result = {  self.get_x() + second.get_x(),
                        self.get_y() + second.get_y() };

    return result;
}

// ----------------------------------------------------------------------

Vector2 operator-(const Vector2& self, const Vector2& second)
{
    Vector2 result = {  self.get_x() - second.get_x(),
                        self.get_y() - second.get_y() };

    return result;
}


// ----------------------------------------------------------------------

Vector2 operator*(const Vector2& self, const double scalar)
{
    Vector2 result = {  self.get_x() * scalar,
                        self.get_y() * scalar };

    return result;
}

// ----------------------------------------------------------------------

Vector2 operator/(const Vector2& self, const double scalar)
{
    Vector2 result = {  self.get_x() / scalar,
                        self.get_y() / scalar };

    return result;
}

// ----------------------------------------------------------------------

void Vector2::print() const
{
    Vector2 vec = *this;

    printf("%g %g\n", vec.x_, vec.y_);
}

// ----------------------------------------------------------------------

static bool is_zero(const double num)
{
    double diff = fabs(num);

    return (diff < EPSILON) ? true : false;
}

// ----------------------------------------------------------------------

Vector3::Vector3(const double x, const double y, const double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// ----------------------------------------------------------------------

Vector3::~Vector3()
{
    x_ = NAN;
    y_ = NAN;
    z_ = NAN;
}

// ----------------------------------------------------------------------

Vector3 operator-(const Vector3& self)
{
    return {-self.get_x(), -self.get_y(), -self.get_z()};
}

// ----------------------------------------------------------------------

Vector3 operator+(const Vector3& self, const Vector3& second)
{
    Vector3 result = {  self.get_x() + second.get_x(),
                        self.get_y() + second.get_y(),
                        self.get_z() + second.get_z() };

    return result;
}

// ----------------------------------------------------------------------

Vector3 operator-(const Vector3& self, const Vector3& second)
{
    Vector3 result = {  self.get_x() - second.get_x(),
                        self.get_y() - second.get_y(),
                        self.get_z() - second.get_z() };

    return result;
}

// ----------------------------------------------------------------------

Vector3 operator*(const Vector3& self, const double scalar)
{
    Vector3 result = {  self.get_x() * scalar,
                        self.get_y() * scalar,
                        self.get_z() * scalar };

    return result;
}

// ----------------------------------------------------------------------

Vector3 operator*(const Vector3& self, const Vector3& second)
{
    Vector3 result = {  self.get_x() * second.get_x(),
                        self.get_y() * second.get_y(),
                        self.get_z() * second.get_z() };

    return result;
}

// ----------------------------------------------------------------------

Vector3 operator/(const Vector3& self, const double scalar)
{
    Vector3 result = {  self.get_x() / scalar,
                        self.get_y() / scalar,
                        self.get_z() / scalar };

    return result;
}

// ----------------------------------------------------------------------

Vector3 Vector3::operator=(const Vector3& second)
{
    x_ = second.x_;
    y_ = second.y_;
    z_ = second.z_;

    return *this;
}

// ----------------------------------------------------------------------

void Vector3::print() const
{
    Vector3 vec = *this;

    printf("%g %g %g\n", vec.x_, vec.y_, vec.z_);
}

// ----------------------------------------------------------------------

Vector3 operator%=(Vector3& self, const double a)
{
    if (self.get_x() >= a)
        self.set_x(a);

    if (self.get_y() >= a)
        self.set_y(a);

    if (self.get_z() >= a)
        self.set_z(a);

    return self;
}

// ----------------------------------------------------------------------

Vector3 Vector3::normalize() const
{
    double len = this->get_length();

    Vector3 result = {x_ / len, y_ / len, z_ / len};

    return result;
}

// ----------------------------------------------------------------------

double cosinus(const Vector3& first, const Vector3& second)
{
    Vector3 third_edge = first - second;

    double a = first.get_length();
    double b = second.get_length();
    double c = third_edge.get_length();

    double cos = (a * a + b * b - c * c) / (2 * a * b);

    return cos;
}

// ----------------------------------------------------------------------

Vector3 reflect_vector(const Vector3& falling, const Vector3& normal)
{
    Vector3 normalized = normal.normalize();

    double length = falling.get_length();
    double cos    = cosinus(falling, normal);

    Vector3 reflected = normalized * (2 * length * cos) - falling;

    return reflected;
}

