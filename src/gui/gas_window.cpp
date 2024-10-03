#include <iostream>

#include "gui/gas_window.hpp"

GasWindow::GasWindow(const size_t length, const size_t width, const Dot& top_left, Model::GasContainer* gas) :
                    Window(length, width, top_left)
{
    gas_ = gas;
}

GasWindow::~GasWindow()
{
    gas_ = nullptr;
}

void GasWindow::draw(Graphics::Desktop& desktop) const
{
    desktop.draw_rectangle(top_left_, length_, width_, sf::Color(200, 200, 200));

    gas_->draw(desktop, *this);
}

double AmountDependance::operator()()
{
    std::vector<Model::Molecule*> molecules = gas_.get_molecules();

    size_t size    = molecules.size();
    size_t typed   = 0;
    size_t overall = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (molecules[i]->is_deleted)
            continue;

        overall++;

        if (molecules[i]->get_type() == type_)
            typed++;
    }

    if (overall == 0)
        return 0;

    return (double) typed;
}

double TemperatureDependance::operator()()
{
    std::vector<Model::Molecule*> molecules = gas_.get_molecules();

    size_t size          = molecules.size();
    size_t overall       = 0;
    double kinetic_total = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (molecules[i]->is_deleted)
            continue;

        overall++;

        double speed = molecules[i]->get_speed().get_length();
        double mass  = molecules[i]->get_mass();

        kinetic_total = mass * speed * speed * 0.5;
    }

    if (overall == 0)
        return 0;

    static const double CAST_TEMP_COEF = 0.0001;

    double temp = ((double) kinetic_total / ((double) overall * CAST_TEMP_COEF));  // / overall 

    return temp;
}

double PressureDependance::operator()()
{
    return gas_.get_pressure();
}

void AddMolecules::operator()(Graphics::Event& event)
{
    for (size_t i = 0; i < amount_; i++)
        gas_.add_molecule(type_, STD_MASS);
}

void RemoveMolecules::operator()(Graphics::Event& event)
{
    for (size_t i = 0; i < amount_; i++)
        gas_.remove_molecule(type_);
}

void MovePiston::operator()(Graphics::Event& event)
{
    Vector last_down_right = gas_.get_down_right();

    Vector new_down_right = {last_down_right.get_x() - delta_, last_down_right.get_y()};

    gas_.set_down_right(new_down_right);
}


