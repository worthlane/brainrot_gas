#ifndef _PIXELS_ARRAY_HPP_
#define _PIXELS_ARRAY_HPP_

#include <cmath>

static const u_int8_t RGB_MAX         = 255;
static const u_int8_t NOT_TRANSPARENT = 255;

struct PixelCondition
{
    u_int8_t red;
    u_int8_t green;
    u_int8_t blue;
    u_int8_t transparency;
};

PixelCondition operator*=(PixelCondition& color, const double coef);
PixelCondition operator+=(PixelCondition& self, const PixelCondition& second);

static const PixelCondition RED_PIXEL   = {RGB_MAX,       0,       0, NOT_TRANSPARENT};
static const PixelCondition GREEN_PIXEL = {      0, RGB_MAX,       0, NOT_TRANSPARENT};
static const PixelCondition BLUE_PIXEL  = {      0,       0, RGB_MAX, NOT_TRANSPARENT};
static const PixelCondition BLACK_PIXEL = {      0,       0,       0, NOT_TRANSPARENT};
static const PixelCondition WHITE_PIXEL = {RGB_MAX, RGB_MAX, RGB_MAX, NOT_TRANSPARENT};

class Pixels
{
    public:
        Pixels(const size_t size);
        Pixels(const size_t length, const size_t width);
        ~Pixels();

        u_int8_t* get_array() const;
        PixelCondition get_pixel_color(const size_t position) const;

        void paint_array(const PixelCondition& color);
        void paint_frame(const PixelCondition& color, const size_t length, const size_t width, const double percent);

        void paint_pixel(const size_t position, const PixelCondition& color);
        void lighten_pixel(const size_t position, const double brightness);

        void clear();

    private:
        size_t    size_;
        u_int8_t* pixels_;
};

#endif // _PIXELS_ARRAY_HPP_
