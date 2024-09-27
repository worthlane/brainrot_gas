#pragma once

#include "model/molecules.hpp"
#include "model/physical.hpp"
#include "maths/coord_system.hpp"
#include "gui/window.hpp"

namespace Scene
{

class GasContainer : public Updatable, WindowDrawable
{
    public:
        GasContainer(const Vector& top_left, const Vector& down_right);
        ~GasContainer();

        Vector get_top_left() const { return physics_.top_left; }
        Vector get_down_right() const { return physics_.down_right; }
        double get_length()   const { return physics_.down_right.get_x() - physics_.top_left.get_x(); }
        double get_width()    const { return physics_.top_left.get_y()   - physics_.down_right.get_y(); }

        void add_molecule(const Scene::MoleculeType type, const Vector& position, const Vector& speed, const double mass);
        void add_molecule(const Scene::MoleculeType type, const double mass);

        void draw(Graphics::Desktop& desktop, const Window& window) const override;

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

    private:
        std::vector<Molecule*> molecules_;

        GasPhysics physics_;
};

}
