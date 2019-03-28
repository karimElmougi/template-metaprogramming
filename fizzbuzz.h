#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <typeinfo>
#include <string>
#include <type_traits>
#include <cstdint>

#include "hdeb.h"
#include "racket.h"

using int_t = uint8_t;

template<int_t N>
struct int_ : public std::integral_constant<int_t, N> {};
struct Fizz { inline static const char value[] = "Fizz"; };
struct Buzz { inline static const char value[] = "Buzz"; };
struct FizzBuzz { inline static const char value[] = "FizzBuzz"; };

template<class T>
struct is_int_ { static const bool value = false; };

template<int_t N>
struct is_int_<int_<N>> { static const bool value = true; };

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

struct afficher_valeur {
	std::ostream &os;
	afficher_valeur(std::ostream &os) : os{ os } {
	}

	template <class T>
	void execute() {
		if constexpr(is_int_<T>::value) {
			os << std::to_string(T::value) << std::endl;
		}
		else {
			os << T::value << std::endl;
		}

	}
};

void fizz_buzz() {
	using input = static_range<int_, 1, 100>::type;
	using fizzbuzz_list = static_map<fizzbuzz, input>::type;
	static_for_each<fizzbuzz_list>{}.execute(afficher_valeur{ std::cout });
}
