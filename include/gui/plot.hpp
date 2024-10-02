#pragma once

#include "graphics/visual.hpp"
#include "gui/window.hpp"
#include "maths/coord_system.hpp"

class Dependence
{
    public:
        virtual double operator()() = 0;
};

class Plot : public Window
{
    public:
        Plot(const size_t length, const size_t width, const Dot& top_left, Dependence* dependence,
             const double max, const double min);
        ~Plot();

        void draw(Graphics::Desktop& window) const override;

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

    private:
        Dependence* dependence_;

        std::vector<double> values_;

        double max_, min_;
        double    accumulating_value_ = 0.0;
        u_int64_t functor_launches_   = 0;
};
