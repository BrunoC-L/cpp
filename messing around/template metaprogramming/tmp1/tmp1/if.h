#pragma once
#include <utility>

namespace if_ns {

	template <typename T>
	concept True = T::value == true;

	template <typename T>
	concept False = T::value == false;

	namespace If_impl {
		template <typename P, typename T, typename F>
		struct If;

		template <True B, typename T, typename U>
		struct If<B, T, U> {
			using type = T;
		};

		template <False B, typename T, typename U>
		struct If<B, T, U> {
			using type = U;
		};
	}

	template <typename... Ts>
	using If = typename If_impl::If<Ts...>::type;
}
