#pragma once
#include <cstdint>
#include "int.h"

template<template <class> class F, class TList>
struct static_map;

template<template <class> class F, class... T>
struct static_map<F, type_list<T...>> {
	using type = type_list<typename F<T>::type...>;
};

template<class Car, class Cdr>
struct cons;

template<class Car, class... Cdr>
struct cons<Car, type_list<Cdr...>> {
	using type = type_list<Car, Cdr...>;
};

template<template<int_t> class T, int_t Begin, int_t End>
struct static_range {
	using type = typename cons<T<Begin>, typename static_range<T, Begin + 1, End>::type>::type;
};

template<template<int_t> class T, int_t N>
struct static_range<T, N, N> {
	using type = type_list<>;
};
