//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14
// XFAIL: libcpp-no-exceptions
// <optional>

// optional<T>& operator=(optional<T>&& rhs);

#include <optional>
#include <string>
#include <type_traits>
#include <utility>

using std::optional;

struct X {};

struct Y
{
    Y() = default;
    Y& operator=(Y&&) { return *this; }
};

struct Z1
{
    Z1() = default;
    Z1(Z1&&) = default;
    Z1& operator=(Z1&&) = delete;
};

struct Z2
{
    Z2() = default;
    Z2(Z2&&) = delete;
    Z2& operator=(Z2&&) = default;
};

#if __cplusplus >= 201402
template <class T>
constexpr bool
test()
{
    optional<T> opt;
    optional<T> opt2;
    opt = std::move(opt2);
    return true;
}
#endif

int main()
{
    {
        using T = int;
        static_assert((std::is_trivially_copy_constructible<optional<T>>::value), "");
#if __cplusplus >= 201402
        static_assert(test<T>(), "");
#endif
    }
    {
        using T = X;
        static_assert((std::is_trivially_copy_constructible<optional<T>>::value), "");
#if __cplusplus >= 201402
        static_assert(test<T>(), "");
#endif
    }
    static_assert(!(std::is_trivially_move_assignable<optional<Y>>::value), "");
    static_assert(!(std::is_trivially_move_assignable<optional<std::string>>::value), "");

    static_assert(!(std::is_move_assignable<optional<Z1>>::value), "");
    static_assert(!(std::is_move_assignable<optional<Z2>>::value), "");
}
