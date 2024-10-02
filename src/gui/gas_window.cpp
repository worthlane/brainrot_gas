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

double PercentageDependence::operator()()
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

    return (double) typed / (double) overall;
}

void AddMolecules::operator()(Graphics::Event& event)
{
    for (size_t i = 0; i < amount_; i++)
        gas_.add_molecule(type_, STD_MASS);
}


