#include <stdio.h>

#include "maths/coord_system.hpp"

static const size_t X_CENTER_STD = 240;
static const size_t Y_CENTER_STD = 320;

static const double DX = 1;
static const double DY = 1;

RectangleSystem::RectangleSystem(const size_t length, const size_t width, const double scale, const Vector2& center) :
    center_(center)
{
    scale_ = scale;

    length_ = length;
    width_  = width;
}

// ----------------------------------------------------------------------

RectangleSystem::~RectangleSystem()
{
    scale_ = NAN;

    width_  = NAN;
    length_ = NAN;
}

// ----------------------------------------------------------------------

size_t RectangleSystem::get_width() const
{
    return width_;
}

// ----------------------------------------------------------------------

size_t RectangleSystem::get_length() const
{
    return length_;
}

// ----------------------------------------------------------------------

Vector2 RectangleSystem::coords_to_pixel(const Vector2& vec)
{
    double x = vec.get_x();
    double y = vec.get_y();

    Vector2 delta = {x, -y};
    delta = delta - center_;

    Vector2 screen_center = {length_ / 2, width_ / 2};

    Vector2 result = screen_center + (delta / scale_);

    return result;
}

// ----------------------------------------------------------------------

Vector2 RectangleSystem::pixel_to_coords(const Vector2& pixel)
{
    Vector2 screen_center = {length_ / 2, width_ / 2};

    Vector2 result = (pixel - screen_center) * scale_;

    Vector2 coords = {result.get_x(), -result.get_y()};

    return coords + center_;
}

// ----------------------------------------------------------------------

double RectangleSystem::get_scale() const
{
    return scale_;
}

// ----------------------------------------------------------------------

void RectangleSystem::set_center(const Vector2& center)
{
    center_ = center;
}
