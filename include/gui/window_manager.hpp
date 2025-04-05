#pragma once

#include "gui/window.hpp"
#include "gui/manager.hpp"
#include "graphics/visual.hpp"

class WindowManager : public Manager<Window>, DesktopDrawable, Updatable
{
    public:
        void draw(Graphics::Desktop& window) const override;
        bool update(Graphics::Desktop& window, Graphics::Event& event) override;
};
