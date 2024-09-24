#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_

#include <vector>
#include <chrono>

#include "graphics/visual.hpp"
#include "graphics/pixels_array.hpp"

Vector2 get_mouse_position(const Graphics::Window& window);

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

class AButton
{
    public:
        AButton(const size_t length, const size_t width, const Dot& upper_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released);
        AButton(const size_t length, const size_t width, const Dot& upper_left);
        ~AButton();

        virtual bool on_default(Graphics::Window& window, Graphics::Event& event) = 0;
        virtual bool on_hover(Graphics::Window& window, Graphics::Event& event)   = 0;
        virtual bool on_click(Graphics::Window& window, Graphics::Event& event)   = 0;
        virtual bool on_release(Graphics::Window& window, Graphics::Event& event) = 0;

        virtual void operator()(Graphics::Event& event) = 0;

        bool is_hovered(const Graphics::Window& window);

        bool update(Graphics::Window& window, Graphics::Event& event);

    protected:
        size_t width_, length_;
        Dot upper_left_;

        ButtonCondition cond_ = ButtonCondition::DEFAULT;

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

class AnimatedButton : public AButton
{
    public:
        AnimatedButton(const size_t length, const size_t width, const Dot& upper_left);
        ~AnimatedButton();

        bool on_default(Graphics::Window& window, Graphics::Event& event) override;
        bool on_hover(Graphics::Window& window, Graphics::Event& event)   override;
        bool on_click(Graphics::Window& window, Graphics::Event& event)   override;
        bool on_release(Graphics::Window& window, Graphics::Event& event) override;

    protected:

        double mask_brightness_;

        std::chrono::milliseconds interact_time_;
        std::chrono::steady_clock::time_point last_update_;

};

#define DRAW_BUTTON_WITH_MASK(window, texture, mask, alpha)             \
                                        do                              \
                                        {                               \
                                            Graphics::Sprite masked;    \
                                            masked.set_texture(mask);   \
                                            masked.set_position(upper_left_.get_x(), upper_left_.get_y());  \
                                            masked.set_color(sf::Color(RGB_MAX, RGB_MAX, RGB_MAX, RGB_MAX * alpha)); \
                                                                                                                    \
                                            Graphics::Sprite origin;    \
                                            origin.set_texture(texture);   \
                                            origin.set_position(upper_left_.get_x(), upper_left_.get_y());  \
                                            origin.set_color(sf::Color(RGB_MAX, RGB_MAX, RGB_MAX, RGB_MAX - RGB_MAX * alpha)); \
                                                                                                                            \
                                            window.draw(origin);                                            \
                                            window.draw(masked);                                            \
                                        } while(0)



#endif // _CONTROLS_HPP_
