#include "gui/window_manager.hpp"

void WindowManager::draw(Graphics::Desktop& window) const
{
    size_t size = objects_.size();

    for (size_t i = 0; i < size; i++)
    {
        objects_[i]->draw(window);
    }
}
