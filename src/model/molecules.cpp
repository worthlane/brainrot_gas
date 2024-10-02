#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <cmath>

#include "model/molecules.hpp"

Model::Molecule::Molecule(const Vector& position, const Vector& speed, const double mass) :
                        position_(position), speed_(speed), mass_(mass), radius_(RADIUS_TO_MASS_COEF * sqrt(mass)), impulse_(speed * mass)
{
}

Model::Molecule::~Molecule()
{
    mass_   = NAN;
    radius_ = NAN;

    position_ = NAN_VECTOR;
    speed_    = NAN_VECTOR;
    impulse_  = NAN_VECTOR;
}

void Model::Molecule::set_impulse(const Vector& impulse)
{
    impulse_ = impulse;
    speed_   = impulse_ / mass_;
}

void Model::SigmaMolecule::draw(Graphics::Desktop& desktop, const Window& window) const
{
    if (is_deleted)
        return;

    CoordSystem system   = window.get_system();
    Vector window_offset = window.get_top_left();

    Vector top_left = window_offset + system.coords_to_pixel({position_.get_x(),
                                                              position_.get_y()});
    double radius = radius_ / system.get_scale();
    Vector center_offset = {radius, radius};
    top_left = top_left - center_offset;

    desktop.draw_circle(top_left, radius, sf::Color::Blue);
}

void Model::SkibidiMolecule::draw(Graphics::Desktop& desktop, const Window& window) const
{
    if (is_deleted)
        return;

    CoordSystem system   = window.get_system();
    Vector window_offset = window.get_top_left();
    double side = 2 * radius_ / system.get_scale();

    Vector top_left = window_offset + system.coords_to_pixel({position_.get_x(),
                                                              position_.get_y()});
    Vector center_offset = {side / 2, side / 2};
    top_left = top_left - center_offset;

    desktop.draw_rectangle(top_left, side, side, sf::Color::Red);
}

bool Model::Molecule::update(Graphics::Desktop& window, Graphics::Event& event)
{
    if (is_deleted)
        return false;

    static const double TICK_COEF = 1e-2;

    position_ = position_ + (speed_ * TICK_COEF);

    return true;
}

bool do_intersect(const Model::Molecule* first, const Model::Molecule* second)
{
    Vector pos1 = first->get_position();
    Vector pos2 = second->get_position();

    double len = first->get_radius() + second->get_radius();

    Vector delta_pos = pos1 - pos2;
    double dist = delta_pos.get_length();

    if (dist > len || first->is_deleted || second->is_deleted)
        return false;

    return true;
}

void Model::Molecule::set_params(const Vector& position, const Vector& impulse, const double mass)
{
    position_ = position;
    impulse_  = impulse;
    mass_     = mass;

    radius_   = RADIUS_TO_MASS_COEF * sqrt(mass_);

    speed_    = impulse_ / mass_;
}



