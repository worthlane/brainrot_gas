#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include "maths/vectors.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "scene/molecules.hpp"

static const double DELTA_ANGLE = 1e-4;
static const size_t LENGTH = 1280;
static const size_t WIDTH  = 720;
static const double SCALE  = 0.05;

static const double AMBIENT = 0.2;

static const Vector2 NULL_VECTOR = {0, 0};

const char* DEFAULT_BUTTON = "assets/textures/button_default.png";
const char* PRESSED_BUTTON = "assets/textures/button_pressed.png";
const size_t BUTTON_LENGTH = 130;
const size_t BUTTON_WIDTH  = 50;

int main()
{
    RectangleSystem  system = {LENGTH, WIDTH, SCALE, {0, 0}};
    Graphics::Window window = {system, "Gas"};

    Scene::SigmaMolecule mol = {{0, 0}, {0, 0}, 1, 1};
    Scene::BetaMolecule mol2 = {{4, 3}, {0, 0}, 1, 2};

    while (window.is_open())
    {
        window.closure_check();

        window.clear();

        mol.draw(window);
        mol2.draw(window);

        window.display();
    }

    return 0;
}
