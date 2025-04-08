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
            Exception(const char* reason, Exception* before = nullptr) noexcept;
            Exception(ErrorCode code, Exception* before = nullptr) noexcept;

            ~Exception() noexcept;

            // Non-copyable
            Exception(const Exception&) = delete;
            Exception& operator=(const Exception&) = delete;

            // Non-movable
            Exception(Exception&&) = delete;
            Exception& operator=(Exception&&) = delete;

            const char* what() const noexcept override;

            Exception* get_prev() const noexcept;

        private:
            Exception* before_;

            const char* reason_;
            ErrorCode   code_;
    };
}
