#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#include "gui/buttons.hpp"

const char* RED_SUBSCRIBE_BUTTON  = "assets/textures/button_default.png";
const char* GRAY_SUBSCRIBE_BUTTON = "assets/textures/button_pressed.png";

// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& top_left,
                const sf::Texture def, const sf::Texture hovered, const sf::Texture pressed, const sf::Texture released, Action* action) :
                Window(length, width, top_left),
                default_(def), hovered_(hovered), pressed_(pressed), released_(released), action_(action)
{
}

// ----------------------------------------------------------------------

AButton::AButton(const size_t length, const size_t width, const Dot& top_left, Action* action) :
                Window(length, width, top_left), action_(action)
{
}

// ----------------------------------------------------------------------

AButton::~AButton()
{
    length_ = NAN;
    width_  = NAN;
}

// ----------------------------------------------------------------------

bool AButton::is_hovered(const Graphics::Desktop& window)
{
    Dot mouse = get_mouse_position(window);

    size_t mouse_x = mouse.get_x();
    size_t mouse_y = mouse.get_y();

    size_t left_x  = top_left_.get_x();
    size_t right_x = left_x + length_;

    size_t upper_y = top_left_.get_y();
    size_t lower_y = upper_y + width_;

    if ((left_x  <= mouse_x && mouse_x <= right_x) &&
        (upper_y <= mouse_y && mouse_y <= lower_y))
        return true;
    else
        return false;
}

// ----------------------------------------------------------------------

bool AButton::update(Graphics::Desktop& window, Graphics::Event& event)
{
    if (last_update_ == 0)
    {
        last_update_ = get_time();
        return false;
    }

    auto current = get_time();
    auto time_passed = current - last_update_;

    bool result = false;

    switch (cond_)
    {
        case ButtonCondition::DEFAULT:
            this->handle_default_(window);
            result = this->on_default(window, event);
            break;

        case ButtonCondition::HOVERED:
            this->handle_hover_(window);
            result = this->on_hover(window, event);
            break;

        case ButtonCondition::PRESSED:
            this->handle_click_(window);
            result = this->on_click(window, event);
            break;

        case ButtonCondition::RELEASED:
            this->handle_release_(window);
            result = this->on_release(window, event);
            break;

        default:

            cond_ = ButtonCondition::DEFAULT;
    }

    last_update_ = current;

    return result;
}

// ----------------------------------------------------------------------

void AButton::handle_default_(Graphics::Desktop& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_hovered)
        cond_ = ButtonCondition::HOVERED;

    if (is_hovered && is_pressed)
        cond_ = ButtonCondition::PRESSED;
}

// ----------------------------------------------------------------------

void AButton::handle_hover_(Graphics::Desktop& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (!is_hovered)
    {
        cond_ = ButtonCondition::DEFAULT;
    }

    if (is_hovered && is_pressed)
        cond_ = ButtonCondition::PRESSED;
}


// ----------------------------------------------------------------------

void AButton::handle_click_(Graphics::Desktop& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (!is_pressed && is_hovered)
        cond_ = ButtonCondition::RELEASED;
    else if (!is_hovered)
        cond_ = ButtonCondition::DEFAULT;
}

// ----------------------------------------------------------------------

void AButton::handle_release_(Graphics::Desktop& window)
{
    bool is_hovered = this->is_hovered(window);
    bool is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    cond_ = ButtonCondition::DEFAULT;
}

// ----------------------------------------------------------------------

bool AButton::on_default(Graphics::Desktop& window, Graphics::Event& event)
{
    return false;
}

// ----------------------------------------------------------------------

bool AButton::on_click(Graphics::Desktop& window, Graphics::Event& event)
{
    return false;
}

// ---------------------------------------------------------------------

bool AButton::on_hover(Graphics::Desktop& window, Graphics::Event& event)
{
    return false;
}

// ----------------------------------------------------------------------

bool AButton::on_release(Graphics::Desktop& window, Graphics::Event& event)
{
    return false;
}

// ----------------------------------------------------------------------

void default_action(void* params)
{
    printf("action\n");
}

// ----------------------------------------------------------------------

RectangleButton::RectangleButton(const size_t length, const size_t width, const Dot& upper_left, Action* action,
                                 const char* default_texture, const char* hovered_texture, const char* pressed_texture, const char* released_texture) :
    AButton(length, width, upper_left, action)
{
    default_.loadFromFile(default_texture);
    hovered_.loadFromFile(hovered_texture);
    pressed_.loadFromFile(pressed_texture);
    released_.loadFromFile(released_texture);
}

// ----------------------------------------------------------------------

RectangleButton::~RectangleButton()
{
}

// ----------------------------------------------------------------------

bool RectangleButtonRelease::on_release(Graphics::Desktop& window, Graphics::Event& event)
{
    auto current = get_time();

    (*action_)(event, current - last_update_);

    return true;
}

// ----------------------------------------------------------------------

bool RectangleButtonHold::on_click(Graphics::Desktop& window, Graphics::Event& event)
{
    auto current = get_time();

    (*action_)(event, current - last_update_);

    return true;
}

// ----------------------------------------------------------------------

void AButton::draw(Graphics::Desktop& window) const
{
    switch (cond_)
    {
        case ButtonCondition::DEFAULT:
            DRAW_BUTTON(window, default_);
            break;

        case ButtonCondition::HOVERED:
            DRAW_BUTTON(window, hovered_);
            break;

        case ButtonCondition::PRESSED:
            DRAW_BUTTON(window, pressed_);
            break;

        case ButtonCondition::RELEASED:
            DRAW_BUTTON(window, released_);
            break;

        default:
            break;
    }
}

