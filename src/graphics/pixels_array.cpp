#include <assert.h>
#include <stdio.h>

#include "graphics/pixels_array.hpp"

Pixels::Pixels(const size_t size)
{
    u_int8_t* pixels = new u_int8_t[size];

    pixels_ = pixels;
    size_   = size;
}

// ----------------------------------------------------------------------

Pixels::Pixels(const size_t length, const size_t width)
{
    u_int8_t* pixels = new u_int8_t[length * width * 4];

    pixels_ = pixels;
    size_   = length * width * 4;
}

// ----------------------------------------------------------------------

Pixels::~Pixels()
{
    delete[] pixels_;

    size_   = NAN;
}

// ----------------------------------------------------------------------

void Pixels::paint_pixel(const size_t position, const PixelCondition& color)
{
    assert(position + 3 < size_);

    pixels_[position]     = color.red;
    pixels_[position + 1] = color.green;
    pixels_[position + 2] = color.blue;
    pixels_[position + 3] = color.transparency;
}

// ----------------------------------------------------------------------

void Pixels::paint_array(const PixelCondition& color)
{
    for (size_t i = 0; i < size_; i += 4)
    {
        this->paint_pixel(i, color);
    }
}

// ----------------------------------------------------------------------

u_int8_t* Pixels::get_array() const
{
    return pixels_;
}

// ----------------------------------------------------------------------

PixelCondition Pixels::get_pixel_color(const size_t position) const
{
    assert((position + 3 < size_) && (position % 4) == 0 &&
           "position should point at the start of pixel info in array");

    return {pixels_[position], pixels_[position + 1], pixels_[position + 2], pixels_[position + 3]};
}

// ----------------------------------------------------------------------

void Pixels::lighten_pixel(const size_t position, const double brightness)
{
    assert((position + 3 < size_) && (position % 4) == 0 &&
           "position should point at the start of pixel info in array");
    assert(brightness >= 0 && brightness <= 1 && "brightness coefficient should be in [0, 1] range");

    PixelCondition color = this->get_pixel_color(position);

    color *= brightness;

    this->paint_pixel(position, color);
}

// ----------------------------------------------------------------------

PixelCondition operator*=(PixelCondition& self, const double coef)
{
    self.red   *= coef;
    self.green *= coef;
    self.blue  *= coef;

    return self;
}

// ----------------------------------------------------------------------

PixelCondition operator+=(PixelCondition& self, const PixelCondition& second)
{
    int red   = self.red          + second.red;
    int green = self.green        + second.green;
    int blue  = self.blue         + second.blue;
    int trans = self.transparency + second.transparency;

    self.red          = (red   >= RGB_MAX) ? RGB_MAX : red;
    self.green        = (green >= RGB_MAX) ? RGB_MAX : green;
    self.blue         = (blue  >= RGB_MAX) ? RGB_MAX : blue;
    self.transparency = (trans >= RGB_MAX) ? RGB_MAX : trans;

    return self;
}

// ----------------------------------------------------------------------

void Pixels::clear()
{
    for (size_t i = 0; i < size_; i++)
        pixels_[i] = 0;
}

// ----------------------------------------------------------------------

void Pixels::paint_frame(const PixelCondition& color, const size_t length, const size_t width, const double percent)
{
    assert(percent <= 1 && percent >= 0);
    assert(length * width * 4 == size_);

    size_t y_size = (width / 2) * percent;
    size_t x_size = (length / 2) * percent;

    for (size_t x = 0; x < length; x++)
    {
        for (size_t y = 0; y < width; y++)
        {
            if (x <= x_size || x >= length - x_size || y <= y_size || y >= width - y_size)
                this->paint_pixel((length * y + x) * 4, color);
        }
    }
}


