#include "gui/button_manager.hpp"

// ----------------------------------------------------------------------

bool ButtonManager::update(Graphics::Desktop& window, Graphics::Event& event)
{
    size_t size = objects_.size();

    bool update_flag = false;

    for (size_t i = 0; i < size; i++)
    {
        bool res = objects_[i]->update(window, event);
        if (res)
            update_flag = true;
    }

    return update_flag;
}
