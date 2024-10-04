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
#include "utils/exceptions.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const char* RED_BUTTON_DEFAULT   = "assets/textures/red_default.png";
static const char* RED_BUTTON_HOVERED   = "assets/textures/red_hovered.png";
static const char* RED_BUTTON_PRESSED   = "assets/textures/red_pressed.png";

static const char* BLUE_BUTTON_DEFAULT   = "assets/textures/blue_default.png";
static const char* BLUE_BUTTON_HOVERED   = "assets/textures/blue_hovered.png";
static const char* BLUE_BUTTON_PRESSED   = "assets/textures/blue_pressed.png";

static const char* LEFT_ARROW_DEFAULT   = "assets/textures/leftarrow_default.png";
static const char* LEFT_ARROW_HOVERED   = "assets/textures/leftarrow_hovered.png";
static const char* LEFT_ARROW_PRESSED   = "assets/textures/leftarrow_pressed.png";

static const char* RIGHT_ARROW_DEFAULT   = "assets/textures/rightarrow_default.png";
static const char* RIGHT_ARROW_HOVERED   = "assets/textures/rightarrow_hovered.png";
static const char* RIGHT_ARROW_PRESSED   = "assets/textures/rightarrow_pressed.png";

static const size_t BUTTON_LENGTH = 179;
static const size_t BUTTON_WIDTH  = 50;

static const size_t ARROW_LENGTH  = 150;
static const size_t ARROW_WIDTH   = 113;


int main()
{
    try
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

        MovePiston move_piston_left = {gas, 0.5};
        MovePiston move_piston_right = {gas, -0.5};

        RemoveMolecules remove_sigma = {gas, Model::MoleculeType::SIGMA, 10};
        RemoveMolecules remove_skibidi = {gas, Model::MoleculeType::SKIBIDI, 10};

        AmountDependance sigma_percentage_dependence   = {gas, Model::MoleculeType::SIGMA};
        AmountDependance skibidi_percentage_dependence = {gas, Model::MoleculeType::SKIBIDI};
        TemperatureDependance temp = {gas};
        PressureDependance press = {gas};

        Plot sigma_percentage = {350, 80, {920, 10}, &sigma_percentage_dependence, 0, 0};
        Plot skibidi_percentage = {350, 80, {920, 120}, &skibidi_percentage_dependence, 0, 0};
        Plot temperature = {350, 80, {920, 230}, &temp, 0, 0};
        Plot pressure = {350, 80, {920, 340}, &press, 0, 0};

        RectangleButton add_sigma_button = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 500}, &add_sigma,
                                            BLUE_BUTTON_DEFAULT, BLUE_BUTTON_HOVERED, BLUE_BUTTON_PRESSED, BLUE_BUTTON_PRESSED};
        RectangleButton add_skibidi_button = {BUTTON_LENGTH, BUTTON_WIDTH, {350, 500}, &add_skibidi,
                                              RED_BUTTON_DEFAULT, RED_BUTTON_HOVERED, RED_BUTTON_PRESSED, RED_BUTTON_PRESSED};
        RectangleButton remove_sigma_button = {BUTTON_LENGTH, BUTTON_WIDTH, {100, 600}, &remove_sigma,
                                               BLUE_BUTTON_DEFAULT, BLUE_BUTTON_HOVERED, BLUE_BUTTON_PRESSED, BLUE_BUTTON_PRESSED};
        RectangleButton remove_skibidi_button = {BUTTON_LENGTH, BUTTON_WIDTH, {350, 600}, &remove_skibidi,
                                                 RED_BUTTON_DEFAULT, RED_BUTTON_HOVERED, RED_BUTTON_PRESSED, RED_BUTTON_PRESSED};
        RectangleButton piston_left = {ARROW_LENGTH, ARROW_WIDTH, {700, 500}, &move_piston_left,
                                       LEFT_ARROW_DEFAULT, LEFT_ARROW_HOVERED, LEFT_ARROW_PRESSED, LEFT_ARROW_DEFAULT};
        RectangleButton piston_right = {ARROW_LENGTH, ARROW_WIDTH, {900, 500}, &move_piston_right,
                                        RIGHT_ARROW_DEFAULT, RIGHT_ARROW_HOVERED, RIGHT_ARROW_PRESSED, RIGHT_ARROW_DEFAULT};

        mgr.add(&sigma_percentage);
        mgr.add(&skibidi_percentage);
        mgr.add(&temperature);
        mgr.add(&pressure);

        mgr.add(&add_sigma_button);
        mgr.add(&add_skibidi_button);
        mgr.add(&remove_sigma_button);
        mgr.add(&remove_skibidi_button);
        mgr.add(&piston_left);
        mgr.add(&piston_right);

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

        }
    }
    catch (const Mystd::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        Mystd::Exception* prev = e.get_prev();

        while (prev != nullptr)
        {
            std::cerr << prev->what() << std::endl;
            prev = prev->get_prev();
        }
    }

    return 0;
}
