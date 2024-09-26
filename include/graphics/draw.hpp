#pragma once

#include "graphics/visual.hpp"

class Drawable
{
    public:
        virtual void draw(Graphics::Window& window) const = 0;
}
