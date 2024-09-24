#ifndef _CONVERTION_HPP_
#define _CONVERTION_HPP_

#include <SFML/Graphics.hpp>

namespace Graphics
{

class Sprite
{
    public:
        Sprite();
        ~Sprite();

        void set_texture(const sf::Texture &texture, bool reset_rect=false);
        void set_position (float x, float y);
        void set_color(sf::Color color);

        sf::Sprite get_sprite() const;

    private:
        sf::Sprite sprite_;
};

class Event
{
    public:
        Event();
        ~Event();

        sf::Event& get_event();
        sf::Event::EventType& type();

    private:
        sf::Event event_;
};

/*class Texture
{
    public:
        Texture();
        ~Texture();



    private:
        sf::Texture texture_;
};*/

}

#endif // CONVERTION_HPP
