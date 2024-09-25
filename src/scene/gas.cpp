#include "scene/gas.hpp"

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static void draw_background(Graphics::Window& window, Scene::Gas& gas);

Scene::Gas::Gas(const Vector2& top_left, const size_t width, const size_t height) :
                top_left_(top_left), width_(width), height_(height)
{

}

// ----------------------------------------------

Scene::Gas::~Gas()
{
    top_left_ = NAN_VECTOR;
    width_ = 0;
    height_ = 0;

    molecules_.clear();
}

// ----------------------------------------------

void Scene::Gas::draw(Graphics::Window& window)
{
    draw_background(window, *this);

    size_t size = molecules_.size();

    for (size_t i = 0; i < size; i++)
    {
        molecules_[i]->draw(window);
        molecules_[i]->move();
    }
}

// ----------------------------------------------

static void draw_background(Graphics::Window& window, Scene::Gas& gas)
{
    Vector2 top_left_coord = gas.get_top_left();

    RectangleSystem system = window.get_system();
    Vector2 top_left_pixel = system.coords_to_pixel(top_left_coord);

    sf::RectangleShape rec;
    rec.setSize({gas.get_width() / system.get_scale(), gas.get_height() / system.get_scale()});
    rec.setPosition(top_left_pixel.get_x(), top_left_pixel.get_y());
    rec.setFillColor(BACKGROUND_COLOR);
    window.window_.draw(rec);
}
