#include <iostream>

#include "scene/physical.hpp"

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

    if ((pos1 - pos2).get_length() > len)
        return;
    else
    {
        Vector impulse1 = first->get_impulse();
        Vector impulse2 = second->get_impulse();

        first->set_impulse(impulse2);
        second->set_impulse(impulse1);
    }
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

    //std::cout << directed_towards({2, -1}, {-1, 0}) << std::endl;

    if (pos.get_y() + radius > upper_limit)
    {
        std::cout << "collide\n";
        elastic_reflection(molecule, UPPER_NORMAL);
    }

    if (pos.get_y() - radius < down_limit)
    {
        std::cout << "collide\n";
        elastic_reflection(molecule, DOWN_NORMAL);
    }

    if (pos.get_x() + radius > right_limit)
    {
        std::cout << "collide\n";
        elastic_reflection(molecule, RIGHT_NORMAL);
    }

    if (pos.get_x() - radius < left_limit)
    {
        std::cout << "collide\n";
        elastic_reflection(molecule, LEFT_NORMAL);
    }
}
