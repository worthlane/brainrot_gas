#include "utils/exceptions.hpp"

namespace Mystd
{
    Exception::Exception(const char* reason, Exception* before) noexcept :
        before_(before), reason_(reason), code_(ErrorCode::UNKNOWN) {}

    Exception::Exception(ErrorCode code, Exception* before) noexcept :
        before_(before), reason_(""), code_(code) {}

    Exception::~Exception() noexcept
    {
        delete before_;
    }

    const char* Exception::what() const noexcept
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

    Exception* Exception::get_prev() const noexcept
    {
        return before_;
    }

}
