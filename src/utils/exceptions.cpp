#include "utils/exceptions.hpp"

namespace Mystd
{
    Exception::Exception(const char* reason, Exception* before) noexcept(true) : reason_(reason), before_(before), code_(ErrorCode::UNKNOWN) {}

    Exception::Exception(ErrorCode code, Exception* before) noexcept(true) : code_(code), before_(before), reason_("") {}

    Exception::~Exception() noexcept(true)
    {
        if (before_)
            delete before_;
    }

    const char* Exception::what() const noexcept(true)
    {
        if (reason_)
            return reason_;
        switch (code_)
        {
            case ErrorCode::OK:
                return "No error\n";
            case ErrorCode::ALLOCATE_FAILED:
                return "Memory allocation failed\n";
            case ErrorCode::UNKNOWN:
            default:
                return "Unknown error\n";
        }
    }

    Exception* Exception::get_prev() const noexcept(true)
    {
        return before_;
    }

}
