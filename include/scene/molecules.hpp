#pragma once

#include "maths/coord_system.hpp"
#include "graphics/pixels_array.hpp"
#include "graphics/visual.hpp"

namespace Scene
{

class Molecule
{
    public:
        Molecule(const Vector& position, const Vector& speed, const double mass, const double radius);
        ~Molecule();

        Vector get_position() const { return position_; }
        Vector get_impulse()  const { return impulse_; }
        Vector get_speed()    const { return speed_; }
        double  get_mass()     const { return mass_; }
        double  get_radius()   const { return radius_; }

        void move();

        void elastic_reflection(const Vector& normal);

        virtual void draw(Graphics::Window& window) = 0;

    protected:
        Vector position_;

        Vector impulse_;
        Vector speed_;

        double  mass_;
        double  radius_;
};

class SigmaMolecule : public Molecule
{
    public:
        SigmaMolecule(const Vector& position, const Vector& speed, const double mass, const double radius) :
            Molecule(position, speed, mass, radius) {}
        ~SigmaMolecule() {}

        void draw(Graphics::Window& window) override;
};

class BetaMolecule : public Molecule
{
    public:
        BetaMolecule(const Vector& position, const Vector& speed, const double mass, const double radius) :
            Molecule(position, speed, mass, radius) {}
        ~BetaMolecule() {}

        void draw(Graphics::Window& window) override;
};


}


double calculate_sphere_z(const Vector& xy, const double radius);
