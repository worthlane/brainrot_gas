#ifndef _GAS_HPP_
#define _GAS_HPP_

#include "scene/molecules.hpp"

namespace Scene
{

class Gas
{
    public:
        Gas(const Vector& top_left, const size_t width, const size_t height);
        ~Gas();

        Vector get_top_left() const { return top_left_; }
        size_t  get_width()  const { return width_; }
        size_t  get_height() const { return height_; }

        void add_molecule(Molecule* molecule) { molecules_.push_back(molecule); }

        void draw(Graphics::Window& window);


    private:
        std::vector<Molecule*> molecules_;

        Vector top_left_;
        size_t  width_, height_;
};

}

#endif // _GAS_HPP_
