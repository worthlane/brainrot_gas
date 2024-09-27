#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "gui/gas_window.hpp"
#include "scene/gas.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const Vector NULL_VECTOR = {0, 0};

const size_t BUTTON_LENGTH = 130;
const size_t BUTTON_WIDTH  = 50;

int main()
{
    Graphics::Desktop desktop = {LENGTH, WIDTH, "Gas"};

    Scene::GasContainer gas = {{15, -15}, {-15, 15}};

    Scene::SigmaMolecule mol = {{0, 0}, {1, 2}, 1, 0.5};
    Scene::SkibidiMolecule mol2 = {{4, 3}, {2, -1}, 1, 1};

    GasWindow window = {1000, 500, {10, 10}, &gas};

    gas.add_molecule(&mol);
    gas.add_molecule(&mol2);

    while (desktop.is_open())
    {
        desktop.closure_check();

        Graphics::Event event;

        desktop.clear();

        window.draw(desktop);
        gas.update(desktop, event);

        desktop.display();
    }

    return 0;
}
