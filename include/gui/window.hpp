#pragma once

#include "graphics/visual.hpp"
#include "maths/vectors.hpp"
#include "maths/coord_system.hpp"

class Window : public DesktopDrawable, public Updatable
{
    public:
        Window(const size_t length, const size_t width, const Dot& top_left_);
        ~Window();

        Vector  get_top_left()   const { return top_left_; }
        size_t  get_width()      const { return width_; }
        size_t  get_length()     const { return length_; }

        CoordSystem get_system() const { return system_; }

        virtual bool update(Graphics::Desktop& window, Graphics::Event& event) { return false; }

    protected:
        size_t width_, length_;
        Dot top_left_;

        CoordSystem system_;
};

class WindowDrawable
{
    public:
        virtual void draw(Graphics::Desktop& desktop, const Window& window) const = 0;
};
