#pragma once

#include "model/molecules.hpp"
#include "model/physical.hpp"
#include "model/chemical.hpp"
#include "maths/coord_system.hpp"
#include "gui/window.hpp"

namespace Model
{

class GasContainer : public Updatable, WindowDrawable
{
    public:
        GasContainer(const Vector& top_left, const Vector& down_right);
        ~GasContainer();

        Vector get_top_left()   const { return physics_.top_left; }
        Vector get_down_right() const { return physics_.down_right; }
        double get_length()     const { return physics_.down_right.get_x() - physics_.top_left.get_x(); }
        double get_width()      const { return physics_.top_left.get_y()   - physics_.down_right.get_y(); }

        double get_pressure()   const { return physics_.pressure; }

        void set_top_left(const Vector& top_left) { physics_.top_left = top_left; }
        void set_down_right(const Vector& down_right) { physics_.down_right = down_right; }

        std::vector<Molecule*>& get_molecules() { return molecules_; }

        void add_molecule(const Model::MoleculeType type, const Vector& position, const Vector& speed, const double mass);
        void add_molecule(const Model::MoleculeType type, const double mass);
        void remove_molecule(const Model::MoleculeType type);
        void add_molecules(std::vector<Model::Molecule*>& new_molecules);

        void draw(Graphics::Desktop& desktop, const Window& window) const override;

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

    private:
        std::vector<Molecule*> molecules_;

        GasPhysics   physics_;
        GasChemistry chemistry_;

        void clear_deleted();
};

}
