#pragma once

#include "gui/window.hpp"
#include "gui/plot.hpp"
#include "model/gas.hpp"

class GasWindow : public Window, DesktopDrawable
{
    public:
        GasWindow(const size_t length, const size_t width, const Dot& top_left, Model::GasContainer* gas);
        ~GasWindow();

        void draw(Graphics::Desktop& window) const override;

    private:
        Model::GasContainer* gas_;
};

class GasDependence : public Dependence
{
    public:
        GasDependence(Model::GasContainer& gas);
        ~GasDependence();

    protected:
        Model::GasContainer& gas_;
};

class PercentageDependence : public GasDependence
{
    public:
        PercentageDependence(Model::GasContainer& gas, Model::MoleculeType type);
        ~PercentageDependence();

        double operator()() override;

    private:
        Model::MoleculeType type_;
};
