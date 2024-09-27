#pragma once

#include "gui/manager.hpp"
#include "model/molecules.hpp"

class GasPhysics : public Manager<Model::Molecule>, Updatable
{
    public:
        GasPhysics(const Vector& top, const Vector& down) : top_left(top), down_right(down) {}
        ~GasPhysics() { top_left = NAN_VECTOR; down_right = NAN_VECTOR; }

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

        Vector top_left;
        Vector down_right;

};
