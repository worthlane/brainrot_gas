#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

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

static const Vector NULL_VECTOR = {0, 0};

const size_t BUTTON_LENGTH = 130;
const size_t BUTTON_WIDTH  = 50;

int main()
{
    srand(time(0));

    Graphics::Desktop desktop = {LENGTH, WIDTH, "Gas"};
    WindowManager mgr;

    Scene::GasContainer gas = {{-20, 10}, {20, -10}};

    Scene::SigmaMolecule mol = {{0, -1}, {10, 7}, 2};
    Scene::SigmaMolecule mol2 = {{0, 0}, {3, 0}, 1};
    Scene::SkibidiMolecule mol3 = {{0, 0}, {3, 2}, 1};

    GasWindow gas_window = {1000, 500, {40, 40}, &gas};

    mgr.add(&gas_window);

    for (size_t i = 0; i < 30; i++)
        gas.add_molecule(Scene::MoleculeType::SIGMA, 1);

    for (size_t i = 0; i < 20; i++)
        gas.add_molecule(Scene::MoleculeType::SKIBIDI, 1);

    /*gas.add_molecule(Scene::MoleculeType::SIGMA, {0, 0}, {3, 0}, 1);
    gas.add_molecule(Scene::MoleculeType::SKIBIDI, {0, 0}, {3, 2}, 1);*/

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
