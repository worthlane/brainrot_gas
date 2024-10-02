#pragma once

#include "graphics/visual.hpp"

template <typename T>
class Manager
{
    public:
        Manager() {}
        ~Manager() { objects_.clear(); }

        void add(T* object) { objects_.push_back(object); }
        void clear() { objects_.clear(); }

    protected:
        std::vector<T*> objects_;
};
