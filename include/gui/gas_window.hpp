#pragma once

#include "gui/window.hpp"
#include "gui/plot.hpp"
#include "gui/buttons.hpp"

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
        GasDependence(Model::GasContainer& gas) : gas_(gas) {}
        ~GasDependence() {}

    protected:
        Model::GasContainer& gas_;
};

class PercentageDependence : public GasDependence
{
    public:
        PercentageDependence(Model::GasContainer& gas, Model::MoleculeType type) : GasDependence(gas), type_(type) {}
        ~PercentageDependence() {}

        double operator()() override;

    private:
        Model::MoleculeType type_;
};

class GasAction : public Action
{
    public:
        GasAction(Model::GasContainer& gas) : gas_(gas) {}
        ~GasAction() {}

    protected:
        Model::GasContainer& gas_;
};

class AddMolecules : public GasAction
{
    public:
        AddMolecules(Model::GasContainer& gas, Model::MoleculeType type, const size_t amount) :
                    GasAction(gas), type_(type), amount_(amount) {}
        ~AddMolecules() {}

        void operator()(Graphics::Event& event) override;

    protected:
        Model::MoleculeType type_;
        size_t amount_;
};
