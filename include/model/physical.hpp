#pragma once

#include "gui/manager.hpp"
#include "model/molecules.hpp"

class GasPhysics : public Manager<Model::Molecule>, public Updatable
{
    public:
        GasPhysics(const Vector& top, const Vector& down) : top_left(top), down_right(down) {}

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

        Vector top_left;
        Vector down_right;

        double pressure = 0;

};
