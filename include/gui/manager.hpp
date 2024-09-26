#pragma once

#include "graphics/visual.hpp"
#include "gui/buttons.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();

        void add_button(AButton* button);

        bool update(Graphics::Window& window, Graphics::Event& event);

    private:
        std::vector<AButton*> buttons_;
};
