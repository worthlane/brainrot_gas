#include "gui/gas_window.hpp"

GasWindow::GasWindow(const size_t length, const size_t width, const Dot& top_left, Scene::GasContainer* gas) :
                    Window(length, width, top_left)
{
    gas_ = gas;
}

GasWindow::~GasWindow()
{
    gas_ = nullptr;
}

void GasWindow::draw(Graphics::Desktop& desktop) const
{
    gas_->draw(desktop, *this);
}
