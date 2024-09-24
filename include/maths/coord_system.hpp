#ifndef _COORD_SYSTEM_HPP_
#define _COORD_SYSTEM_HPP_

#include "maths/vectors.hpp"

class RectangleSystem
{
    public:
        RectangleSystem(const size_t length, const size_t width, const double scale, const Vector2& center);
        ~RectangleSystem();

        size_t get_width()  const;
        size_t get_length() const;
        double get_scale()  const;

        Vector2 coords_to_pixel(const Vector2& vec);

        Vector2 pixel_to_coords(const Vector2& pixel);

        void set_center(const Vector2& center);

    private:
        double scale_;
        Dot    center_;
        size_t width_, length_;
};

#endif // _COORD_SYSTEM_HPP
