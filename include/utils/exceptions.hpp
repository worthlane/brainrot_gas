#pragma once

#include <exception>
#include <string>

namespace Mystd
{
    enum class ErrorCode
    {
        OK = 0,

        ALLOCATE_FAILED,

        UNKNOWN,
    };

    class Exception : public std::exception
    {
        public:
            Exception(const char* reason, Exception* before = nullptr) noexcept(true);
            Exception(ErrorCode code, Exception* before = nullptr) noexcept(true);

            ~Exception() noexcept(true);

            const char* what() const noexcept(true);

            Exception* get_prev() const noexcept(true);

        private:
            Exception* before_;

            const char* reason_;
            ErrorCode   code_;


    };
}
