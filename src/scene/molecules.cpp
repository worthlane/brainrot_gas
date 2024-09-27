#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "scene/molecules.hpp"

Scene::Molecule::Molecule(const Vector& position, const Vector& speed, const double mass, const double radius) :
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

void Scene::Molecule::set_impulse(const Vector& impulse)
{
    impulse_ = impulse;
    speed_   = impulse_ / mass_;
}

void Scene::SigmaMolecule::draw(Graphics::Desktop& desktop, const Window& window) const
{
    CoordSystem system   = window.get_system();
    Vector window_offset = window.get_top_left();

    Vector top_left = window_offset + system.coords_to_pixel({position_.get_x(),
                                                              position_.get_y()});

    sf::CircleShape circle;
    circle.setRadius(radius_ / system.get_scale());
    circle.setPosition(top_left.get_x(), top_left.get_y());
    circle.setFillColor(sf::Color::Blue);
    desktop.window_.draw(circle);
}

void Scene::SkibidiMolecule::draw(Graphics::Desktop& desktop, const Window& window) const
{
    CoordSystem system   = window.get_system();
    Vector window_offset = window.get_top_left();

    Vector top_left = window_offset + system.coords_to_pixel({position_.get_x(),
                                                              position_.get_y()});

    sf::RectangleShape rec;
    rec.setSize({radius_ / system.get_scale(), radius_ / system.get_scale()});
    rec.setPosition(top_left.get_x(), top_left.get_y());
    rec.setFillColor(sf::Color::Red);
    desktop.window_.draw(rec);
}

bool Scene::Molecule::update(Graphics::Desktop& window, Graphics::Event& event)
{
    static const double TICK_COEF = 5e-4;

    position_ = position_ + (speed_ * TICK_COEF);
}



