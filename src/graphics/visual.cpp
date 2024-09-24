#include "graphics/visual.hpp"

static const float DOT_RADIUS = 1.0;

static const Vector2 NULL_VECTOR = {0, 0};

// ==============================================================

Graphics::Window::Window(const RectangleSystem& system, const char* name) :
    window_(sf::VideoMode(system.get_length(), system.get_width()), name),
    system_(system)
{
}

// ----------------------------------------------------------------------

Graphics::Window::~Window()
{
    window_.close();
}

// ----------------------------------------------------------------------

bool Graphics::Window::is_open()
{
    return window_.isOpen();
}

// ----------------------------------------------------------------------

void Graphics::Window::clear()
{
    window_.clear();
}

// ----------------------------------------------------------------------

void Graphics::Window::display()
{
    window_.display();
}

// ----------------------------------------------------------------------

void Graphics::Window::close()
{
    window_.close();
}

// ----------------------------------------------------------------------

void Graphics::Window::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

// ----------------------------------------------------------------------

void Graphics::Window::draw(const Graphics::Sprite& sprite) // TODO convert
{
    window_.draw(sprite.get_sprite());
}

// ----------------------------------------------------------------------

void Graphics::Window::set_system(const RectangleSystem& system)
{
    system_ = system;
}

// ------------------------------------------

bool Graphics::Window::poll_event(Event& event)
{
    return window_.pollEvent(event.get_event());
}
