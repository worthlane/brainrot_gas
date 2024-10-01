#include <cassert>
#include <iostream>
#include <cmath>

#include <stdio.h>

#include "model/chemical.hpp"
#include "utils/2Dvtable.hpp"

static std::vector<Model::Molecule*> no_reaction(Model::Molecule* self, Model::Molecule* other) { return {}; }

static std::vector<Model::Molecule*> sigma_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> sigma_skibidi_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> skibidi_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static std::vector<Model::Molecule*> skibidi_skibidi_collide(Model::Molecule* self, Model::Molecule* other);

static void fill_vtable(TwoDVtable<reaction_t>& vtable);

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

static std::vector<Model::Molecule*> sigma_skibidi_collide(Model::Molecule* self, Model::Molecule* other)
{
    assert(typeid(*self)  == typeid(Model::SigmaMolecule));
    assert(typeid(*other) == typeid(Model::SkibidiMolecule));

    double mass = self->get_mass() + other->get_mass();
    Vector impulse = self->get_impulse() + other->get_impulse();

    other->set_params(other->get_position(), impulse, mass);

    self->is_deleted = true;

    return {};
}

static std::vector<Model::Molecule*> skibidi_sigma_collide(Model::Molecule* self, Model::Molecule* other)
{
    assert(typeid(*self)  == typeid(Model::SkibidiMolecule));
    assert(typeid(*other) == typeid(Model::SigmaMolecule));

    return sigma_skibidi_collide(other, self);
}

static std::vector<Model::Molecule*> skibidi_skibidi_collide(Model::Molecule* self, Model::Molecule* other)
{
    assert(typeid(*self) == typeid(Model::SkibidiMolecule));
    assert(typeid(*other) == typeid(Model::SkibidiMolecule));

    double total_mass    = self->get_mass() + other->get_mass();
    Vector total_impulse = self->get_impulse() + other->get_impulse();
    Vector collide_pos   = (self->get_position() + other->get_position()) / 2;
    double center_dist   = self->get_radius() + other->get_radius();

    int    sigmas_amount     = total_mass / STD_MASS;
    Vector absolute_impulse  = total_impulse / sigmas_amount;

    std::vector<Model::Molecule*> result;

    for (int i = 0; i < sigmas_amount; i++)
    {
        double angle = 2 * M_PI * i / sigmas_amount;

        Vector relative  = {cos(angle), sin(angle)};

        Vector spawn_pos = collide_pos + relative * center_dist;
        Vector impulse   = absolute_impulse + relative;

        Model::Molecule* sigma = new Model::SigmaMolecule(spawn_pos, impulse, STD_MASS);
        result.push_back(sigma);
    }

    self->is_deleted = true;
    other->is_deleted = true;

    return result;
}


std::vector<Model::Molecule*> GasChemistry::update(Graphics::Desktop& window, Graphics::Event& event)
{
    TwoDVtable<reaction_t> vtable(Model::MOLECULE_TYPES, no_reaction);
    fill_vtable(vtable);

    size_t size = objects_.size();

    static const double needed_impulse = (STD_MASS * sqrt(2));

    std::vector<Model::Molecule*> new_molecules;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (do_intersect(objects_[i], objects_[j]))
            {
                Vector impulse1 = objects_[i]->get_impulse();
                Vector impulse2 = objects_[j]->get_impulse();

                Model::MoleculeType type1 = objects_[i]->get_type();
                Model::MoleculeType type2 = objects_[j]->get_type();

                if (impulse1.get_length() + impulse2.get_length() < needed_impulse)
                    continue;

                std::vector<Model::Molecule*> res;

                res = vtable[static_cast<size_t>(type1)][static_cast<size_t>(type2)](objects_[i], objects_[j]);

                size_t res_size = res.size();

                for (size_t k = 0; k < res_size; k++)
                    new_molecules.push_back(res[k]);
            }
        }
    }

    return new_molecules;
}

static void fill_vtable(TwoDVtable<reaction_t>& vtable)
{
    vtable[static_cast<size_t>(Model::MoleculeType::SIGMA)][static_cast<size_t>(Model::MoleculeType::SIGMA)]     = sigma_sigma_collide;
    vtable[static_cast<size_t>(Model::MoleculeType::SIGMA)][static_cast<size_t>(Model::MoleculeType::SKIBIDI)]   = sigma_skibidi_collide;
    vtable[static_cast<size_t>(Model::MoleculeType::SKIBIDI)][static_cast<size_t>(Model::MoleculeType::SIGMA)]   = skibidi_sigma_collide;
    vtable[static_cast<size_t>(Model::MoleculeType::SKIBIDI)][static_cast<size_t>(Model::MoleculeType::SKIBIDI)] = skibidi_skibidi_collide;
}


