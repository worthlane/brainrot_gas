#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/convertion.hpp"
#include "maths/vectors.hpp"

namespace Graphics
{

class Desktop
{
    public:
        Desktop(const size_t length, const size_t width, const char* name);
        ~Desktop();

        bool is_open();
        void clear();
        void display();
        void close();
        void closure_check();

        bool poll_event(Event& event);

        void draw(const Sprite& sprite);

        sf::RenderWindow window_;

        private:
            size_t width_, length_;
};

}

class DesktopDrawable
{
    public:
        virtual void draw(Graphics::Desktop& window) const = 0;
};

Vector get_mouse_position(const Graphics::Desktop& window);

