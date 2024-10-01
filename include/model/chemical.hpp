#pragma once

#include "gui/manager.hpp"
#include "model/molecules.hpp"

typedef std::vector<Model::Molecule*> (*reaction_t)(Model::Molecule* self, Model::Molecule* other);

class GasChemistry : public Manager<Model::Molecule>
{
    public:
        std::vector<Model::Molecule*> update(Graphics::Desktop& window, Graphics::Event& event);

};
