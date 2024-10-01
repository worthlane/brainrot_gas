#include <cassert>
#include <iostream>

#include "model/chemical.hpp"

typedef std::vector<Model::Molecule*> (*reaction_t)(Model::Molecule* self, Model::Molecule* other);

static std::vector<Model::Molecule*> sigma_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> sigma_skibidi_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> skibidi_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> skibidi_skibidi_collide(Model::Molecule* self, Model::Molecule* other);

static std::vector<Model::Molecule*> sigma_sigma_collide(Model::Molecule* self, Model::Molecule* other)
{
    assert(typeid(*self)  == typeid(Model::SigmaMolecule));
    assert(typeid(*other) == typeid(Model::SigmaMolecule));

    double mass = self->get_mass() + other->get_mass();
    Vector impulse = self->get_impulse() + other->get_impulse();

    Model::Molecule* result = new Model::SkibidiMolecule((self->get_position() + other->get_position()) / 2,
                                                          impulse / mass,
                                                          mass);

    self->is_deleted = true;
    other->is_deleted = true;

    return {result};
}

std::vector<Model::Molecule*> GasChemistry::update(Graphics::Desktop& window, Graphics::Event& event)
{
    size_t size = objects_.size();

    std::vector<Model::Molecule*> new_molecules;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (do_intersect(objects_[i], objects_[j]) && objects_[i]->get_type() == Model::MoleculeType::SIGMA
                                                       && objects_[j]->get_type() == Model::MoleculeType::SIGMA)
            {
                std::vector<Model::Molecule*> res = sigma_sigma_collide(objects_[i], objects_[j]);

                size_t res_size = res.size();

                for (size_t k = 0; k < res_size; k++)
                    new_molecules.push_back(res[k]);
            }
        }
    }

    return new_molecules;
}


