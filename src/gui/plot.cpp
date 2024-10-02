#include <cmath>
#include <iostream>

#include "gui/plot.hpp"

static const sf::Color PLOT_BACKGROUND = sf::Color(10,   9, 134);
static const sf::Color PLOT_LINE       = sf::Color(56, 191, 255);

static const size_t PLOT_FRAME_REFRESH = 100;

Plot::Plot(const size_t length, const size_t width, const Dot& top_left, Dependence* dependence,
            const double max, const double min) :
            Window(length, width, top_left), dependence_(dependence), max_(max), min_(min)
{
    for (size_t i = 0; i < length; i++)
    {
        values_.push_back(NAN);
    }
}

Plot::~Plot()
{
    min_ = NAN;
    max_ = NAN;
}

bool Plot::update(Graphics::Desktop& window, Graphics::Event& event)
{
    //std::cout << plot_frame++ << std::endl;

    plot_frame_++;

    accumulating_value_ += (*dependence_)();

    if (plot_frame_ % PLOT_FRAME_REFRESH != 0)
        return false;

    plot_frame_ = 0;

    //std::cout << accumulating_value_ << std::endl;
    //std::cout << (double) PLOT_FRAME_REFRESH << std::endl;

    double new_value = accumulating_value_ / (double) PLOT_FRAME_REFRESH;
    accumulating_value_ = 0.0;

    size_t size = values_.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        values_[i] = values_[i + 1];
    }

    values_[size - 1] = new_value;

    return true;
}

void Plot::draw(Graphics::Desktop& window) const
{
    window.draw_rectangle(top_left_, length_, width_, PLOT_BACKGROUND);

    size_t amount = values_.size();

    for (size_t x = 0; x < amount; x++)
    {
        double val = values_[x];

        if (isnan(val) || val > max_ || val < min_)
            continue;

        size_t x_pos = top_left_.get_x() + x;
        size_t y_pos = top_left_.get_y() + width_ - (values_[x] / (max_ - min_)) * width_;

        window.draw_circle({x_pos, y_pos}, 1, PLOT_LINE);
    }
}
