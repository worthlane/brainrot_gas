#pragma once

#include "graphics/visual.hpp"

class Updatable
{
    public:
        virtual bool update(Graphics::Desktop& window, Graphics::Event& event) = 0;

};

template <typename T>
class Manager
{
    public:
        Manager() {}
        ~Manager() { objects_.clear(); }

        void add(T* object) { objects_.push_back(object); }

    protected:
        std::vector<T*> objects_;
};
