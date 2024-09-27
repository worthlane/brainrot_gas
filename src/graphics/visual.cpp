#include "graphics/visual.hpp"

static const float DOT_RADIUS = 1.0;

static const Vector NULL_VECTOR = {0, 0};

// ==============================================================

Graphics::Desktop::Desktop(const size_t length, const size_t width, const char* name) :
    window_(sf::VideoMode(length, width), name),
    width_(width), length_(length)
{
}

// ----------------------------------------------------------------------

Graphics::Desktop::~Desktop()
{
    window_.close();
}

// ----------------------------------------------------------------------

bool Graphics::Desktop::is_open()
{
    return window_.isOpen();
}

// ----------------------------------------------------------------------

void Graphics::Desktop::clear()
{
    window_.clear();
}

// ----------------------------------------------------------------------

void Graphics::Desktop::display()
{
    window_.display();
}

// ----------------------------------------------------------------------

void Graphics::Desktop::close()
{
    window_.close();
}

// ----------------------------------------------------------------------

void Graphics::Desktop::closure_check()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

// ----------------------------------------------------------------------

void Graphics::Desktop::draw(const Graphics::Sprite& sprite) // TODO convert
{
    window_.draw(sprite.get_sprite());
}

// ------------------------------------------

bool Graphics::Desktop::poll_event(Event& event)
{
    return window_.pollEvent(event.get_event());
}

// ------------------------------------------

void Graphics::Desktop::draw_circle(const Vector& pos, const double radius, sf::Color color)
{
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(pos.get_x(), pos.get_y());
    circle.setFillColor(color);
    window_.draw(circle);
}

// ------------------------------------------

void Graphics::Desktop::draw_rectangle(const Vector& pos, const double length, const double width, sf::Color color)
{
    sf::RectangleShape rec;
    rec.setSize({length, width});
    rec.setPosition(pos.get_x(), pos.get_y());
    rec.setFillColor(color);
    window_.draw(rec);
}

// ----------------------------------------------------------------------

Vector get_mouse_position(const Graphics::Desktop& window)
{
    sf::Vector2i vector = sf::Mouse::getPosition(window.window_);

    size_t x = vector.x;
    size_t y = vector.y;

    static const size_t Y_SHIFT = 0;
    static const size_t X_SHIFT = 0;

    Vector pos = {x - X_SHIFT, y - Y_SHIFT};

    return pos;
}

