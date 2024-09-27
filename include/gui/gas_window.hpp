#pragma once

#include "gui/window.hpp"
#include "model/gas.hpp"

class GasWindow : public Window, DesktopDrawable
{
    public:
        GasWindow(const size_t length, const size_t width, const Dot& top_left, Scene::GasContainer* gas);
        ~GasWindow();

        void draw(Graphics::Desktop& window) const override;

    private:
        Scene::GasContainer* gas_;
};
