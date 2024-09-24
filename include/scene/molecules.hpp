#ifndef _MOLECULES_HPP_
#define _MOLECULES_HPP_

#include "maths/coord_system.hpp"
#include "graphics/pixels_array.hpp"
#include "graphics/visual.hpp"

namespace Scene
{

class Molecule
{
    public:
        Molecule(const Vector2& position, const Vector2& speed, const double mass, const double radius);
        ~Molecule();

        Vector2 get_position() const { return position_; }
        Vector2 get_impulse()  const { return impulse_; }
        Vector2 get_speed()    const { return speed_; }
        double  get_mass()     const { return mass_; }
        double  get_radius()   const { return radius_; }

        virtual void draw(Graphics::Window& window) = 0;

    protected:
        Vector2 position_;

        Vector2 impulse_;
        Vector2 speed_;

        double  mass_;
        double  radius_;
};

class SigmaMolecule : public Molecule
{
    public:
        SigmaMolecule(const Vector2& position, const Vector2& speed, const double mass, const double radius) :
            Molecule(position, speed, mass, radius) {}
        ~SigmaMolecule() {}

        void draw(Graphics::Window& window) override;
};

class BetaMolecule : public Molecule
{
    public:
        BetaMolecule(const Vector2& position, const Vector2& speed, const double mass, const double radius) :
            Molecule(position, speed, mass, radius) {}
        ~BetaMolecule() {}

        void draw(Graphics::Window& window) override;
};


}


double calculate_sphere_z(const Vector2& xy, const double radius);

#endif // _MOLECULES_HPP_
