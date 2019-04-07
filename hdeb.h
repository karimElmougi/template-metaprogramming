#pragma once
#include <iostream>
#include <string>
#include <type_traits>

template <class...>
struct type_list;

template <class>
struct static_head;

template <class T, class ... Q>
struct static_head<type_list<T, Q...>> {
	using type = T;
};

template <class TL>
using static_head_t = typename static_head<TL>::type;

template <template <class, class> class F, class Init, class TList>
struct static_accumulate;

template <template <class, class> class F, class Init, class TL>
using static_accumulate_t = typename static_accumulate<F, Init, TL>::type;

template <template <class, class> class F, class Init, class T, class ... Q>
struct static_accumulate<F, Init, type_list<T, Q...>> {
	using type =
		typename F<T, static_accumulate_t<F, Init, type_list<Q...>>>::type;
};

template <template <class, class> class F, class Init, class T>
struct static_accumulate<F, Init, type_list<T>> {
	using type = typename F<T, Init>::type;
};

template <class TList>
struct static_for_each;

template <class T, class ... Q>
struct static_for_each<type_list<T, Q...>> {
	template <class Op>
	static void execute(Op oper) {
		oper.execute<T>();
		static_for_each<type_list<Q...>>::execute(oper);
	}
};

template <>
struct static_for_each<type_list<>> {
	template <class Op>
	static void execute(Op) {
	}
};

class afficher_nom
{
	std::ostream &os;
public:
	afficher_nom(std::ostream &os) : os{ os } {
	}

	template <class T>
	void execute() {
		os << typeid(T).name() << std::endl;
	}
};
