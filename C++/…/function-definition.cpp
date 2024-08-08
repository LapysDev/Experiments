#include <type_traits>

enum GLenum {};

void glDrawArraysIndirect(GLenum, const void*);

namespace detail {
    struct dummy;

    template<typename T>
    dummy& glDrawArraysIndirect(T, const void*);
}

constexpr bool is_defined()
{
    using namespace detail;
    using ftype = decltype(glDrawArraysIndirect(GLenum(), nullptr));
    return std::is_same<ftype, void>();
}

static_assert(is_defined(), "not defined");
