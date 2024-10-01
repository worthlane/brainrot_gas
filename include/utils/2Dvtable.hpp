#pragma once

template <typename T>
class TwoDVtable
{
    public:
        TwoDVtable(const size_t size, const T value) : vtable_(size, std::vector<T>(size, value)) {}
        ~TwoDVtable() {}

        std::vector<T>& operator[](const size_t i) { return vtable_[i]; }

    private:
        std::vector<std::vector<T>> vtable_;
};
