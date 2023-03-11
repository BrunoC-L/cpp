#pragma once

namespace equality_ns {

	template <typename t, typename u>
	struct _equals;

	template <typename T>
	struct _equals<T, T> {
		using type = T;
	};

	template <typename T, typename U>
	using equality = typename _equals<T, U>::type;
}
