#pragma once

namespace Mystd
{
    template <typename T>
    class Vector
    {
        public:
            Vector() = default;
            Vector(const size_t capacity, const T value = T());


            ~Vector();
        private:
            size_t size_     = 0;
            size_t capacity_ = 0;
            T*     data_     = nullptr;

    }
}

