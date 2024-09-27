#include <iostream>

#include "model/gas.hpp"

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static void draw_container(const Scene::GasContainer& gas, Graphics::Desktop& desktop, const Window& window);

Scene::GasContainer::GasContainer(const Vector& top_left, const Vector& down_right) :
                                physics_(top_left, down_right)
{
}

// ----------------------------------------------

Scene::GasContainer::~GasContainer()
{
    size_t size = molecules_.size();

    for (size_t i = 0; i < size; i++)
    {
        delete molecules_[i];
    }

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

void Scene::GasContainer::add_molecule(const Scene::MoleculeType type, const Vector& position, const Vector& speed, const double mass)
{
    Scene::Molecule* molecule = nullptr;

    switch (type)
    {
        case (Scene::MoleculeType::SKIBIDI):
            molecule = new Scene::SkibidiMolecule(position, speed, mass);
            break;
        case (Scene::MoleculeType::SIGMA):
            molecule = new Scene::SigmaMolecule(position, speed, mass);
            break;
        default:
            return;
    }

    molecules_.push_back(molecule); // TODO trace trap
    physics_.add(molecule);
}

// ----------------------------------------------

void Scene::GasContainer::add_molecule(const Scene::MoleculeType type, const double mass)
{
    Scene::Molecule* molecule = nullptr;

    static const double FIX_WALL_COLLISION = 0.8;

    Dot top_left = this->get_top_left();
    Dot down_right = this->get_down_right();

    Vector position = {rand_double(top_left.get_x(), down_right.get_x()),
                       rand_double(down_right.get_y(), top_left.get_y())};
    Vector speed = {rand_double(-1, 1), rand_double(-1, 1)};

    this->add_molecule(type, position, speed, mass);
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

