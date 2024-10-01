#pragma once

#include "gui/manager.hpp"
#include "model/molecules.hpp"

class GasChemistry : public Manager<Model::Molecule>
{
    public:
        std::vector<Model::Molecule*> update(Graphics::Desktop& window, Graphics::Event& event);

};
