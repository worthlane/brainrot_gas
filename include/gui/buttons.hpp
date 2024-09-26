#pragma once

#include <vector>
#include <chrono>

#include "graphics/visual.hpp"

Vector get_mouse_position(const Graphics::Window& window);

enum class ButtonCondition
{
    DEFAULT,
    HOVERED,
    PRESSED,
    RELEASED
};

enum class ButtonType
{
    HOLD,
    RELEASE,
    DISABLED
};

class Action
{
    public:
        virtual void operator()(Graphics::Event& event) = 0;
};

class AButton
{
    public:
        AButton(const size_t length, const size_t width, const Dot& upper_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released, Action* action);
        AButton(const size_t length, const size_t width, const Dot& upper_left, Action* action);
        ~AButton();

        virtual bool on_default(Graphics::Window& window, Graphics::Event& event);
        virtual bool on_hover(Graphics::Window& window, Graphics::Event& event);
        virtual bool on_click(Graphics::Window& window, Graphics::Event& event);
        virtual bool on_release(Graphics::Window& window, Graphics::Event& event);

        bool is_hovered(const Graphics::Window& window);

        bool update(Graphics::Window& window, Graphics::Event& event);

    protected:
        size_t width_, length_;
        Dot upper_left_;

        ButtonCondition cond_ = ButtonCondition::DEFAULT;

        Action* action_;

        sf::Texture default_;
        sf::Texture hovered_;
        sf::Texture pressed_;
        sf::Texture released_;

        void handle_default_(Graphics::Window& window);
        void handle_hover_(Graphics::Window& window);
        void handle_click_(Graphics::Window& window);
        void handle_release_(Graphics::Window& window);
};

#define DRAW_BUTTON(window, texture)    do                              \
                                        {                               \
                                            Graphics::Sprite sprite;    \
                                            sprite.set_texture(texture);\
                                            sprite.set_position(upper_left_.get_x(), upper_left_.get_y());  \
                                            window.draw(sprite);                                            \
                                        } while(0)

void default_action(void* params);
