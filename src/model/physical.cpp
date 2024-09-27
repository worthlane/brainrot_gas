#include <iostream>

#include "model/physical.hpp"

static const Vector UPPER_NORMAL = {0, -1};
static const Vector RIGHT_NORMAL = {-1, 0};
static const Vector LEFT_NORMAL  = { 1, 0};
static const Vector DOWN_NORMAL  = { 0, 1};

static void collide(Scene::Molecule* first, Scene::Molecule* second);
static void elastic_reflection(Scene::Molecule* mol, const Vector& normal);
static void wall_collision(Scene::Molecule* mol, const Vector& top_left, const Vector& down_right);

// ===================================================================

bool GasPhysics::update(Graphics::Desktop& window, Graphics::Event& event)
{
    size_t size = objects_.size();

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
            collide(objects_[i], objects_[j]);

        wall_collision(objects_[i], top_left, down_right);
    }

    for (size_t i = 0; i < size; i++)
    {
        objects_[i]->update(window, event);
    }

    return true;
}

//-------------------------------------------------------------------

static void collide(Scene::Molecule* first, Scene::Molecule* second)
{
    Vector pos1 = first->get_position();
    Vector pos2 = second->get_position();

    double len = first->get_radius() + second->get_radius();

    Vector delta_pos = pos1 - pos2;
    double dist = delta_pos.get_length();

    if (dist > len)
        return;

    Vector impulse1 = first->get_impulse();
    Vector impulse2 = second->get_impulse();

    Vector normal = (pos2 - pos1).normalize();
    normal.normalize();

    double proj1 = impulse1 * normal;
    double proj2 = impulse2 * normal;

    Vector tangent1 = impulse1 - normal * proj1;
    Vector tangent2 = impulse2 - normal * proj2;

    Vector new_impulse1 = tangent1 + normal * proj2;
    Vector new_impulse2 = tangent2 + normal * proj1;

    first->set_impulse(new_impulse1);
    second->set_impulse(new_impulse2);

    double penetration_depth = len - dist;
    Vector correction_vector = normal * (penetration_depth / 2);

    first->set_position(pos1 - correction_vector);
    second->set_position(pos2 + correction_vector);
}

//-------------------------------------------------------------------

static void elastic_reflection(Scene::Molecule* mol, const Vector& normal)
{
    Vector new_impulse = reflect_vector(mol->get_impulse(), normal);

    mol->set_impulse(new_impulse);
}

//-------------------------------------------------------------------

static void wall_collision(Scene::Molecule* molecule, const Vector& top_left, const Vector& down_right)
{
    double upper_limit = top_left.get_y();
    double down_limit  = down_right.get_y();
    double left_limit  = top_left.get_x();
    double right_limit = down_right.get_x();

    double radius = molecule->get_radius();
    Vector pos    = molecule->get_position();
    Vector speed  = molecule->get_speed();

    if (pos.get_y() + radius > upper_limit)
    {
        elastic_reflection(molecule, UPPER_NORMAL);
        molecule->set_position({pos.get_x(), upper_limit - radius});
    }

    if (pos.get_y() - radius < down_limit)
    {
        elastic_reflection(molecule, DOWN_NORMAL);
        molecule->set_position({pos.get_x(), down_limit + radius});
    }

    if (pos.get_x() + radius > right_limit)
    {
        elastic_reflection(molecule, RIGHT_NORMAL);
        molecule->set_position({right_limit - radius, pos.get_y()});
    }

    if (pos.get_x() - radius < left_limit)
    {
        elastic_reflection(molecule, LEFT_NORMAL);
        molecule->set_position({left_limit + radius, pos.get_y()});
    }
}
