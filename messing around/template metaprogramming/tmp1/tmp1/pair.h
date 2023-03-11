#pragma once
#include "int.h"
#include "if.h"
#include "assertion.h"
#include <utility>

namespace pair {

	using int_ns::Int;

	using if_ns::If;

	template <typename _First, typename _Second>
	struct Pair;

	namespace _Pair_Get {
		template <typename T, typename Index>
		struct Get;

		template <typename T, typename U>
		struct Get<Pair<T, U>, Int<0>> {
			using type = T;
		};

		template <typename T, typename U>
		struct Get<Pair<T, U>, Int<1>> {
			using type = U;
		};
	}

	template <typename T, typename Index>
	using Get = typename _Pair_Get::Get<T, Index>::type;

	template <typename _First, typename _Second>
	struct Pair {

		using type = Pair<_First, _Second>;

		using First = _First;

		using Second = _Second;

		template <typename Index>
		using Get = Get<type, Index>;

		using Size = Int<2>;

		using Reverse = Pair<Second, First>;

		using Index = Pair<Pair<Int<0>, First>, Pair<Int<1>, Second>>;

		using Head = First;

		using Tail = Second;

		template <typename T>
		using Join = T;

		using _t = struct {};

		template <typename E>
		using Contains = typename std::disjunction<std::is_same<E, First>, std::is_same<E, Second>>::type;

		template <typename E>
		using IndexOf = If<
			typename std::is_same<E, First>::type,
			Int<0>,
			If<
			typename std::is_same<E, Second>::type,
				Int<1>,
				equality_ns::equality<Contains<E>, std::true_type>
			>
		>;
	};
}
