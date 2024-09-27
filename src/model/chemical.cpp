#include "chemical.hpp"

typedef void (*reaction_t)(Model::Molecule* self, Model::Molecule* other);

static void sigma_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static void sigma_skibidi_collide(Model::Molecule* self, Model::Molecule* other);
static void skibidi_sigma_collide(Model::Molecule* self, Model::Molecule* other);
static void skibidi_skibidi_collide(Model::Molecule* self, Model::Molecule* other);


