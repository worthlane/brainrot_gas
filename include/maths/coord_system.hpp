#pragma once

#include "maths/vectors.hpp"

class CoordSystem
{
    public:
        CoordSystem(const size_t length, const size_t width, const double scale, const Vector& center);
        ~CoordSystem();

        size_t get_width()  const;
        size_t get_length() const;
        double get_scale()  const;

        Vector coords_to_pixel(const Vector& vec);

        Vector pixel_to_coords(const Vector& pixel);

        void set_center(const Vector& center);

    private:
        double scale_;
        Dot    center_;
        size_t width_, length_;
};
