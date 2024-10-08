#pragma once

#include <vector>
#include <chrono>

#include "graphics/visual.hpp"
#include "gui/window.hpp"
#include "gui/manager.hpp"

enum class ButtonCondition
{
    DEFAULT,
    HOVERED,
    PRESSED,
    RELEASED
};

class Action
{
    public:
        virtual void operator()(Graphics::Event& event, const u_int64_t time_since_update = 0) = 0;
};

class AButton : public Window
{
    public:
        AButton(const size_t length, const size_t width, const Dot& top_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released, Action* action);
        AButton(const size_t length, const size_t width, const Dot& top_left, Action* action);
        ~AButton();

        virtual bool on_default(Graphics::Desktop& window, Graphics::Event& event);
        virtual bool on_hover(Graphics::Desktop& window, Graphics::Event& event);
        virtual bool on_click(Graphics::Desktop& window, Graphics::Event& event);
        virtual bool on_release(Graphics::Desktop& window, Graphics::Event& event);

        bool is_hovered(const Graphics::Desktop& window);

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;
        void draw(Graphics::Desktop& window) const override;

    protected:

        ButtonCondition cond_ = ButtonCondition::DEFAULT;

        Action* action_;

        sf::Texture default_;
        sf::Texture hovered_;
        sf::Texture pressed_;
        sf::Texture released_;

        void handle_default_(Graphics::Desktop& window);
        void handle_hover_(Graphics::Desktop& window);
        void handle_click_(Graphics::Desktop& window);
        void handle_release_(Graphics::Desktop& window);
};

#define DRAW_BUTTON(window, texture)    do                              \
                                        {                               \
                                            Graphics::Sprite sprite;    \
                                            sprite.set_texture(texture);\
                                            sprite.set_position(top_left_.get_x(), top_left_.get_y());  \
                                            window.draw(sprite);                                            \
                                        } while(0)

void default_action(void* params);

class RectangleButton : public AButton
{
    public:
        RectangleButton(const size_t length, const size_t width, const Dot& upper_left, Action* action,
                        const char* default_texture, const char* hovered_texture, const char* pressed_texture, const char* released_texture);
        ~RectangleButton();
};

class RectangleButtonRelease : public RectangleButton
{
    public:
        RectangleButtonRelease(const size_t length, const size_t width, const Dot& upper_left, Action* action,
                               const char* default_texture, const char* hovered_texture, const char* pressed_texture, const char* released_texture) :
                               RectangleButton(length, width, upper_left, action, default_texture, hovered_texture, pressed_texture, released_texture) {}
        ~RectangleButtonRelease() {}

        bool on_release(Graphics::Desktop& window, Graphics::Event& event)   override;
};

class RectangleButtonHold : public RectangleButton
{
    public:
        RectangleButtonHold(const size_t length, const size_t width, const Dot& upper_left, Action* action,
                               const char* default_texture, const char* hovered_texture, const char* pressed_texture, const char* released_texture) :
                               RectangleButton(length, width, upper_left, action, default_texture, hovered_texture, pressed_texture, released_texture) {}
        ~RectangleButtonHold() {}

        bool on_click(Graphics::Desktop& window, Graphics::Event& event)   override;
};
