#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "scene/molecules.hpp"

Scene::Molecule::Molecule(const Vector2& position, const Vector2& speed, const double mass, const double radius) :
                position_(position), speed_(speed), mass_(mass), radius_(radius), impulse_(speed * mass)
{
}

Scene::Molecule::~Molecule()
{
    mass_   = NAN;
    radius_ = NAN;

    position_ = NAN_VECTOR;
    speed_    = NAN_VECTOR;
    impulse_  = NAN_VECTOR;
}

void Scene::SigmaMolecule::draw(Graphics::Window& window)
{
    RectangleSystem system = window.get_system();
    Vector2 top_left = system.coords_to_pixel({position_.get_x() - radius_,
                                               position_.get_y() - radius_});

    sf::CircleShape circle;
    circle.setRadius(radius_ / system.get_scale());
    circle.setPosition(top_left.get_x(), top_left.get_y());
    circle.setFillColor(sf::Color::Blue);
    window.window_.draw(circle);
}

void Scene::BetaMolecule::draw(Graphics::Window& window)
{
    RectangleSystem system = window.get_system();
    Vector2 top_left = system.coords_to_pixel({position_.get_x() - radius_,
                                               position_.get_y() - radius_});

    sf::RectangleShape rec;
    rec.setSize({radius_ / system.get_scale(), radius_ / system.get_scale()});
    rec.setPosition(top_left.get_x(), top_left.get_y());
    rec.setFillColor(sf::Color::Red);
    window.window_.draw(rec);
}


