#include <iostream>

#include "scene/gas.hpp"

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static void draw_container(const Scene::GasContainer& gas, Graphics::Desktop& desktop, const Window& window);
//static void check_wall_collisions(Scene::Gas& gas, Scene::Molecule* molecule);

Scene::GasContainer::GasContainer(const Vector& top_left, const Vector& down_right) :
                                physics_(top_left, down_right)
{
}

// ----------------------------------------------

Scene::GasContainer::~GasContainer()
{
    molecules_.clear();
}

// ----------------------------------------------

void Scene::GasContainer::draw(Graphics::Desktop& desktop, const Window& window) const
{
    draw_container(*this, desktop, window);

    size_t size = molecules_.size();

    for (size_t i = 0; i < size; i++)
    {
        molecules_[i]->draw(desktop, window);
    }
}

// ----------------------------------------------

bool Scene::GasContainer::update(Graphics::Desktop& window, Graphics::Event& event)
{
    return physics_.update(window, event);
}

// ----------------------------------------------

void Scene::GasContainer::add_molecule(Molecule* molecule)
{
    molecules_.push_back(molecule);
    physics_.add(molecule);
}

// ----------------------------------------------

static void draw_container(const Scene::GasContainer& gas, Graphics::Desktop& desktop, const Window& window)
{
    CoordSystem system  = window.get_system();
    Vector pixel_offset = window.get_top_left();
    Vector top_left     = gas.get_top_left();
    Vector top_pixel    = pixel_offset + system.coords_to_pixel(top_left);

    double pixel_width  = gas.get_width() / system.get_scale();
    double pixel_length = gas.get_length() / system.get_scale();

    desktop.draw_rectangle(top_pixel, pixel_length, pixel_width, BACKGROUND_COLOR);
}

// ----------------------------------------------

