#include <iostream>

#include "scene/gas.hpp"

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static const Vector UPPER_NORMAL = {0, -1};
static const Vector RIGHT_NORMAL = {-1, 0};
static const Vector LEFT_NORMAL  = {1, 0};
static const Vector DOWN_NORMAL  = {0, 1};

static void draw_background(Graphics::Window& window, Scene::Gas& gas);
static void check_wall_collisions(Scene::Gas& gas, Scene::Molecule* molecule);

Scene::Gas::Gas(const Vector& top_left, const double width, const double height) :
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

        check_wall_collisions(*this, molecules_[i]);
    }
}

// ----------------------------------------------

static void draw_background(Graphics::Window& window, Scene::Gas& gas)
{
    Vector top_left_coord = gas.get_top_left();

    RectangleSystem system = window.get_system();
    Vector top_left_pixel = system.coords_to_pixel(top_left_coord);

    sf::RectangleShape rec;
    rec.setSize({gas.get_width() / system.get_scale(), gas.get_height() / system.get_scale()});
    rec.setPosition(top_left_pixel.get_x(), top_left_pixel.get_y());
    rec.setFillColor(BACKGROUND_COLOR);
    window.window_.draw(rec);
}

// ----------------------------------------------

static void check_wall_collisions(Scene::Gas& gas, Scene::Molecule* molecule)
{
    double upper_limit = gas.get_top_left().get_y();
    double down_limit  = gas.get_top_left().get_y() - gas.get_height();
    double left_limit  = gas.get_top_left().get_x();
    double right_limit = gas.get_top_left().get_x() + gas.get_width();

    double radius = molecule->get_radius();
    Vector pos    = molecule->get_position();
    Vector speed  = molecule->get_speed();

    std::cout << directed_towards({2, -1}, {-1, 0}) << std::endl;

    if (pos.get_y() + radius > upper_limit && directed_towards(speed, UPPER_NORMAL))
    {
        std::cout << "collide\n";
        molecule->elastic_reflection(UPPER_NORMAL);
    }

    if (pos.get_y() - radius < down_limit && directed_towards(speed, DOWN_NORMAL))
    {
        std::cout << "collide\n";
        molecule->elastic_reflection(DOWN_NORMAL);
    }

    if (pos.get_x() + radius > right_limit && directed_towards(speed, RIGHT_NORMAL))
    {
        std::cout << "collide\n";
        molecule->elastic_reflection(RIGHT_NORMAL);
    }

    if (pos.get_x() - radius < left_limit && directed_towards(speed, LEFT_NORMAL))
    {
        std::cout << "collide\n";
        molecule->elastic_reflection(LEFT_NORMAL);
    }

}
