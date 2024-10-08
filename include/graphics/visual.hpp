#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/convertion.hpp"
#include "maths/vectors.hpp"

#include <chrono>

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
        void draw_circle(const Vector& pos, const double radius, sf::Color color);
        void draw_rectangle(const Vector& pos, const double length, const double width, sf::Color color);
        void draw_image(const Vector& pos, const char* path);
        //void draw_line(const Vector& start, const Vector& end, sf::Color color);

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

class Updatable
{
    public:
        virtual bool update(Graphics::Desktop& window, Graphics::Event& event) {};

        u_int64_t last_update_ = 0;

};

u_int64_t get_time();

Vector get_mouse_position(const Graphics::Desktop& window);

