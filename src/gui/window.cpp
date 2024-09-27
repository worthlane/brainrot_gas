#include "gui/window.hpp"

static const double SCALE  = 0.05;

Window::Window(const size_t length, const size_t width, const Dot& top_left) :
        width_(width), length_(length), top_left_(top_left), system_(length, width, SCALE, {0, 0})
{}


Window::~Window()
{}


