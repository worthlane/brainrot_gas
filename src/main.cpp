#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include <time.h>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "gui/gas_window.hpp"
#include "gui/window_manager.hpp"
#include "model/gas.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

int main()
{
    srand(time(0));

    Graphics::Desktop desktop = {LENGTH, WIDTH, "Gas"};
    WindowManager mgr;

    Model::GasContainer gas = {{-20, 10}, {20, -10}};

    GasWindow gas_window = {900, 500, {100, 100}, &gas};

    mgr.add(&gas_window);

    for (size_t i = 0; i < 100; i++)
        gas.add_molecule(Model::MoleculeType::SIGMA, STD_MASS);

    for (size_t i = 0; i < 0; i++)
        gas.add_molecule(Model::MoleculeType::SKIBIDI, STD_MASS);

    /*gas.add_molecule(Model::MoleculeType::SKIBIDI, {0, -2}, {0, 0}, 1);
    gas.add_molecule(Model::MoleculeType::SKIBIDI, {0, 0}, {0, 0}, 2);
    gas.add_molecule(Model::MoleculeType::SKIBIDI, {0, 2}, {0, 0}, 3);*/

    while (desktop.is_open())
    {
        desktop.closure_check();

        Graphics::Event event;

        desktop.clear();

        mgr.draw(desktop);
        gas.update(desktop, event);

        desktop.display();
    }

    return 0;
}
