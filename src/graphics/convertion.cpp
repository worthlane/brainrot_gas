#include "graphics/convertion.hpp"

// ----------------------------------------------------------------------

Graphics::Sprite::Sprite()
{
    sf::Sprite sprite_;
}

// ----------------------------------------------------------------------

Graphics::Sprite::~Sprite()
{
}

// ----------------------------------------------------------------------

void Graphics::Sprite::set_texture(const sf::Texture &texture, bool reset_rect)
{
    sprite_.setTexture(texture, reset_rect);
}

// ----------------------------------------------------------------------

void Graphics::Sprite::set_position(float x, float y)
{
    sprite_.setPosition(x, y);
}

// ----------------------------------------------------------------------

sf::Sprite Graphics::Sprite::get_sprite() const
{
    return sprite_;
}

// ----------------------------------------------------------------------

void Graphics::Sprite::set_color(sf::Color color)
{
    sprite_.setColor(color);
}

// ----------------------------------------------------------------------

Graphics::Event::Event()
{
    sf::Event event_;
}

// ----------------------------------------------------------------------

Graphics::Event::~Event()
{
}

// ----------------------------------------------------------------------

sf::Event& Graphics::Event::get_event()
{
    return event_;
}

// ----------------------------------------------------------------------

sf::Event::EventType& Graphics::Event::type()
{
    return event_.type;
}
