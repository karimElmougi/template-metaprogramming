#pragma once
#include <cstdint>

using int_t = uint32_t;

template<int_t N>
struct int_ : public std::integral_constant<int_t, N> {};

template<class T>
struct is_int_ { static const bool value = false; };

template<int_t N>
struct is_int_<int_<N>> { static const bool value = true; };
