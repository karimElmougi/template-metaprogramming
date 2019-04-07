#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <typeinfo>
#include <string>
#include <type_traits>
#include <cstdint>

#include "hdeb.h"
#include "racket.h"

struct Fizz { inline static const char value[] = "Fizz"; };
struct Buzz { inline static const char value[] = "Buzz"; };
struct FizzBuzz { inline static const char value[] = "FizzBuzz"; };

template<class N, bool fizz = !(N::value % 3), bool buzz = !(N::value % 5)>
struct fizzbuzz_impl { using type = N; };

template<int_t N>
struct fizzbuzz_impl<int_<N>, true, false> { using type = Fizz; };

template<int_t N>
struct fizzbuzz_impl<int_<N>, false, true> { using type = Buzz; };

template<int_t N>
struct fizzbuzz_impl<int_<N>, true, true> { using type = FizzBuzz; };

template<class N>
using fizzbuzz = fizzbuzz_impl<N>;

void run() {
	using input = static_range<int_, 1, 100>::type;
	using fizzbuzz_list = static_map<fizzbuzz, input>::type;
	static_for_each<fizzbuzz_list>{}.execute(afficher_valeur{ std::cout });
}
