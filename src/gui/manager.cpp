#include "gui/manager.hpp"

// ----------------------------------------------------------------------

Manager::Manager()
{
    std::vector<AButton*> button_;
}

// ----------------------------------------------------------------------

Manager::~Manager()
{
}

// ----------------------------------------------------------------------

void Manager::add_button(AButton* button)
{
    buttons_.push_back(button);
}

// ----------------------------------------------------------------------

bool Manager::update(Graphics::Window& window, Graphics::Event& event)
{
    size_t size = buttons_.size();

    bool update_flag = false;

    for (size_t i = 0; i < size; i++)
    {
        bool res = buttons_[i]->update(window, event);
        if (res)
            update_flag = true;
    }

    return update_flag;
}
