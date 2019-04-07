#pragma once
#include <iostream>
#include <cstdint>

#include "hdeb.h"
#include "racket.h"

template<int_t N>
struct fib { static const auto value = fib<N - 1>::value + fib<N - 2>::value; };

template<>
struct fib<0> { static const auto value = 0; };

template<>
struct fib<1> { static const auto value = 1; };

template<class T>
struct fib_int_ { using type = fib<T::value>; };

template<int_t I>
struct static_fib {
	int_t value;
	static_fib<I - 1> rest;
	static_fib() : value{ fib<I> ::value } {}
};

template<>
struct static_fib<0> {
	int_t value;
	static_fib() : value{ fib<0>::value } {}
};

void static_output() {
	using input = static_range<int_, 0, 30>::type;
	using fib_list = static_map<fib_int_, input>::type;
	static_for_each<fib_list>{}.execute(afficher_valeur{ std::cout });
}

void runtime_output() {
	enum { N = 30 };
	static_fib<N> s;

	for (auto i = 0; i < N; i++)
		std::cout << reinterpret_cast<int*>(&s)[N - i] << std::endl;
}

void run() {
	runtime_output();
}
