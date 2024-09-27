#pragma once

#include "scene/molecules.hpp"
#include "scene/physical.hpp"
#include "maths/coord_system.hpp"
#include "gui/window.hpp"

namespace Scene
{

class GasContainer : public Updatable, WindowDrawable
{
    public:
        GasContainer(const Vector& top_left, const Vector& down_right);
        ~GasContainer();

        void add_molecule(Molecule* molecule);

        void draw(Graphics::Desktop& desktop, const Window& window) const override;

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

    private:
        std::vector<Molecule*> molecules_;

        GasPhysics physics_;
};

}
