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

    GasWindow gas_window = {850, 450, {10, 10}, &gas};

    mgr.add(&gas_window);

    for (size_t i = 0; i < 50; i++)
        gas.add_molecule(Model::MoleculeType::SIGMA, STD_MASS);

    for (size_t i = 0; i < 50; i++)
        gas.add_molecule(Model::MoleculeType::SKIBIDI, STD_MASS);

    AddMolecules add_sigma = {gas, Model::MoleculeType::SIGMA, 10};
    AddMolecules add_skibidi = {gas, Model::MoleculeType::SKIBIDI, 10};

    PercentageDependence sigma_percentage_dependence   = {gas, Model::MoleculeType::SIGMA};
    PercentageDependence skibidi_percentage_dependence = {gas, Model::MoleculeType::SKIBIDI};

    Plot sigma_percentage = {200, 100, {900, 10}, &sigma_percentage_dependence, 1, 0};
    Plot skibidi_percentage = {200, 100, {900, 120}, &skibidi_percentage_dependence, 1, 0};

    RectangleButton add_sigma_button = {130, 50, {10, 500}, &add_sigma};
    RectangleButton add_skibidi_button = {130, 50, {200, 500}, &add_skibidi};

    mgr.add(&sigma_percentage);
    mgr.add(&skibidi_percentage);

    mgr.add(&add_sigma_button);
    mgr.add(&add_skibidi_button);

    clock_t time = clock();

    while (desktop.is_open())
    {
        desktop.closure_check();

        Graphics::Event event;

        desktop.clear();

        mgr.update(desktop, event);
        mgr.draw(desktop);
        gas.update(desktop, event);

        /*std::cout << clock() - time << std::endl;
        time = clock();*/

        desktop.display();

        //sf::sleep(sf::seconds(0.001));
    }

    return 0;
}
