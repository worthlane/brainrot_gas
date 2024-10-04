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

// =====================================

class GasDependence : public Dependence
{
    public:
        GasDependence(Model::GasContainer& gas) : gas_(gas) {}
        ~GasDependence() {}

    protected:
        Model::GasContainer& gas_;
};

class AmountDependance : public GasDependence
{
    public:
        AmountDependance(Model::GasContainer& gas, Model::MoleculeType type) : GasDependence(gas), type_(type) {}
        ~AmountDependance() {}

        double operator()() override;

    private:
        Model::MoleculeType type_;
};

class TemperatureDependance : public GasDependence
{
    public:
        TemperatureDependance(Model::GasContainer& gas) : GasDependence(gas) {}
        ~TemperatureDependance() {}

        double operator()() override;
};

class PressureDependance : public GasDependence
{
    public:
        PressureDependance(Model::GasContainer& gas) : GasDependence(gas) {}
        ~PressureDependance() {}

        double operator()() override;
};

// =================================

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

        void operator()(Graphics::Event& event, const u_int64_t time_since_update = 0) override;

    protected:
        Model::MoleculeType type_;
        size_t amount_;
};

class RemoveMolecules : public GasAction
{
    public:
        RemoveMolecules(Model::GasContainer& gas, Model::MoleculeType type, const size_t amount) :
                    GasAction(gas), type_(type), amount_(amount) {}
        ~RemoveMolecules() {}

        void operator()(Graphics::Event& event, const u_int64_t time_since_update = 0) override;

    protected:
        Model::MoleculeType type_;
        size_t amount_;
};

class MovePiston : public GasAction
{
    public:
        MovePiston(Model::GasContainer& gas, const double delta) :
                    GasAction(gas), delta_(delta) {}
        ~MovePiston() {}

        void operator()(Graphics::Event& event, const u_int64_t time_since_update = 0) override;

    protected:
        double delta_;
};
