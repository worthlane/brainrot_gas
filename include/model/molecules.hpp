#pragma once

#include "maths/coord_system.hpp"
#include "graphics/visual.hpp"
#include "gui/manager.hpp"
#include "gui/window.hpp"

static const double RADIUS_TO_MASS_COEF = 0.5;

namespace Model
{

class Molecule : public WindowDrawable, Updatable
{
    public:
        Molecule(const Vector& position, const Vector& speed, const double mass);
        ~Molecule();

        Vector get_position() const { return position_; }
        Vector get_impulse()  const { return impulse_; }
        Vector get_speed()    const { return speed_; }
        double get_mass()     const { return mass_; }
        double get_radius()   const { return radius_; }

        void   set_impulse(const Vector& impulse);
        void   set_position(const Vector& position) { position_ = position; }

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

        bool is_deleted = false;

    protected:
        Vector position_;

        Vector impulse_;
        Vector speed_;

        double mass_;
        double radius_;
};

enum class MoleculeType
{
    SIGMA   = 0,
    SKIBIDI = 1,
};

class SigmaMolecule : public Molecule
{
    public:
        SigmaMolecule(const Vector& position, const Vector& speed, const double mass) :
            Molecule(position, speed, mass) { }
        ~SigmaMolecule() { }

        void draw(Graphics::Desktop& desktop, const Window& window) const override;
};

class SkibidiMolecule : public Molecule
{
    public:
        SkibidiMolecule(const Vector& position, const Vector& speed, const double mass) :
            Molecule(position, speed, mass) { }
        ~SkibidiMolecule() {}

        void draw(Graphics::Desktop& desktop, const Window& window) const override;
};

}
