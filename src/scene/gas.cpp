#include <iostream>

#include "scene/gas.hpp"

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static void draw_background(Graphics::Desktop& desktop, const Window& window);
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
    draw_background(desktop, window);

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

static void draw_background(Graphics::Desktop& desktop, const Window& window)
{
    Vector top_left = window.get_top_left();

    sf::RectangleShape rec;
    rec.setSize({window.get_length(), window.get_width()});
    rec.setPosition(top_left.get_x(), top_left.get_y());
    rec.setFillColor(BACKGROUND_COLOR);
    desktop.window_.draw(rec);
}

// ----------------------------------------------

