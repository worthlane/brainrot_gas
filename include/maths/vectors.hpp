#ifndef _VECTORS_HPP_
#define _VECTORS_HPP_

#include <cmath>

class Vector2
{
    public:
        Vector2(const double x, const double y);
        ~Vector2();

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_length() const { return sqrt(x_ * x_ + y_ * y_); }

        Vector2 operator=(const Vector2& second);

        void print() const;

    private:
        double x_, y_;
};
typedef Vector2 Dot;

Vector2 operator-(const Vector2& self);
Vector2 operator-(const Vector2& self, const Vector2& second);
Vector2 operator+(const Vector2& self, const Vector2& second);
Vector2 operator*(const Vector2& self, const double scalar);
Vector2 operator/(const Vector2& self, const double scalar);

static const Vector2 NAN_VECTOR = {NAN, NAN};

class Vector3
{
    public:
        Vector3(const double x, const double y, const double z);
        ~Vector3();

        void set_x(const double x) { x_ = x; }
        void set_y(const double y) { y_ = y; }
        void set_z(const double z) { z_ = z; }

        Vector3 operator=(const Vector3& second);

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_z() const { return z_; }
        double get_length() const { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

        Vector3 normalize() const;

        void print() const;

    private:
        double x_, y_, z_;
};

Vector3 reflect_vector(const Vector3& falling, const Vector3& normal);
double  cosinus(const Vector3& first, const Vector3& second);

Vector3 operator-(const Vector3& self);
Vector3 operator-(const Vector3& self, const Vector3& second);
Vector3 operator+(const Vector3& self, const Vector3& second);
Vector3 operator*(const Vector3& self, const double scalar);
Vector3 operator*(const Vector3& self, const Vector3& second);
Vector3 operator%=(Vector3& self, const double a);
Vector3 operator/(const Vector3& self, const double scalar);

#endif // _VECTORS_HPP_
