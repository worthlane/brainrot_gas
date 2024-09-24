#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "graphics/visual.hpp"
#include "gui/controls.hpp"

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

#endif // _MANAGER_HPP_
