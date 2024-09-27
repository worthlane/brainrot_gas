#pragma once

#include "gui/buttons.hpp"
#include "gui/manager.hpp"

class ButtonManager : public Manager<AButton>, Updatable
{
    public:
        ButtonManager() {}
        ~ButtonManager() {}

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;
};
