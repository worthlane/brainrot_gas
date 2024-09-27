#pragma once

#include "gui/manager.hpp"
#include "model/molecules.hpp"

class GasChemistry : public Manager<Model::Molecule>, Updatable
{
    public:
        GasPhysics() {}
        ~GasPhysics() {}

        bool update(Graphics::Desktop& window, Graphics::Event& event) override;

};
