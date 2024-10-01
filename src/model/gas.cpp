#include <iostream>

#include "model/gas.hpp"

static size_t       frame_number  = 0;
static const size_t FRAME_REFRESH = 10;

static const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 50);

static void draw_container(const Model::GasContainer& gas, Graphics::Desktop& desktop, const Window& window);

Model::GasContainer::GasContainer(const Vector& top_left, const Vector& down_right) :
                                physics_(top_left, down_right)
{
}

// ----------------------------------------------

Model::GasContainer::~GasContainer()
{
    size_t size = molecules_.size();

    for (size_t i = 0; i < size; i++)
    {
        delete molecules_[i];
    }

    molecules_.clear();
}

// ----------------------------------------------

void Model::GasContainer::draw(Graphics::Desktop& desktop, const Window& window) const
{
    draw_container(*this, desktop, window);

    size_t size = molecules_.size();

    for (size_t i = 0; i < size; i++)
    {
        molecules_[i]->draw(desktop, window);
    }
}

// ----------------------------------------------

bool Model::GasContainer::update(Graphics::Desktop& window, Graphics::Event& event)
{
    std::vector<Model::Molecule*> new_molecules = chemistry_.update(window, event);

    this->add_molecules(new_molecules);

    physics_.update(window, event);

    if (frame_number++ % FRAME_REFRESH == 0)
    {
        this->clear_deleted();
        frame_number = 0;
    }

    return true;
}

// ----------------------------------------------

void Model::GasContainer::add_molecules(std::vector<Model::Molecule*>& new_molecules)
{
    size_t size = new_molecules.size();

    for (size_t i = 0; i < size; i++)
    {
        molecules_.push_back(new_molecules[i]);

        physics_.add(new_molecules[i]);
        chemistry_.add(new_molecules[i]);
    }
}

// ----------------------------------------------

void Model::GasContainer::add_molecule(const Model::MoleculeType type, const Vector& position, const Vector& speed, const double mass)
{
    Model::Molecule* molecule = nullptr;

    switch (type)
    {
        case (Model::MoleculeType::SKIBIDI):
            molecule = new Model::SkibidiMolecule(position, speed, mass);
            break;
        case (Model::MoleculeType::SIGMA):
            molecule = new Model::SigmaMolecule(position, speed, mass);
            break;
        default:
            return;
    }

    molecules_.push_back(molecule); // TODO trace trap
    physics_.add(molecule);
    chemistry_.add(molecule);
}

// ----------------------------------------------

void Model::GasContainer::add_molecule(const Model::MoleculeType type, const double mass)
{
    Model::Molecule* molecule = nullptr;

    static const double FIX_WALL_COLLISION = 0.8;

    Dot top_left = this->get_top_left();
    Dot down_right = this->get_down_right();

    Vector position = {rand_double(top_left.get_x(), down_right.get_x()),
                       rand_double(down_right.get_y(), top_left.get_y())};
    Vector speed = {rand_double(-1, 1), rand_double(-1, 1)};

    this->add_molecule(type, position, speed, mass);
}

// ----------------------------------------------

static void draw_container(const Model::GasContainer& gas, Graphics::Desktop& desktop, const Window& window)
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

void Model::GasContainer::clear_deleted()
{
    size_t before_size = molecules_.size();

    std::vector<Model::Molecule*> cleared;

    for (size_t i = 0; i < before_size; i++)
    {
        if (!molecules_[i]->is_deleted)
            cleared.push_back(molecules_[i]);
    }

    physics_.clear();
    chemistry_.clear();

    size_t new_size = cleared.size();

    for (size_t i = 0; i < new_size; i++)
    {
        physics_.add(cleared[i]);
        chemistry_.add(cleared[i]);
    }

    molecules_.swap(cleared);
}

