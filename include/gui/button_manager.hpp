#pragma once

#include "gui/buttons.hpp"
#include "gui/manager.hpp"

class ButtonManager : public Manager<AButton>, Updatable
{
    public:
        bool update(Graphics::Desktop& window, Graphics::Event& event) override;
};
