#pragma once

template <typename...>
struct types {};

template <typename T>
struct Type {
	using type = T;
};

namespace detail {
	template <typename...>
	struct _join;

	template <typename... Ts, typename... Us>
	struct _join<types<Ts...>, types<Us...>> {
		using type = types<Ts..., Us...>;
	};
}

template <typename... Ts>
using join = typename detail::_join<Ts...>::type;

namespace detail {
	template <template <typename, typename> typename, typename, typename>
	struct _reduce;

	template <template <typename, typename> typename F, typename T>
	struct _reduce<F, T, types<>> {
		using type = typename T;
	};

	template <template <typename, typename> typename F, typename T, typename U, typename... Ts>
	struct _reduce<F, T, types<U, Ts...>> {
		using type = typename _reduce<F, F<T, U>, types<Ts...>>::type;
	};
}

template <template <typename, typename> typename F, typename T, typename Types>
using reduce = typename detail::_reduce<F, T, Types>::type;

namespace detail {
	template <template <typename, typename> typename, typename, typename>
	struct _reduce2;

	template <template <typename, typename> typename F, typename T>
	struct _reduce2<F, T, types<>> {
		using type = typename Type<T>;
	};

	template <template <typename, typename> typename F, typename T, typename U, typename... Ts>
	struct _reduce2<F, T, types<U, Ts...>> {
		using type = typename _reduce2<F, typename F<T, U>::type, types<Ts...>>::type;
	};
}

template <template <typename, typename> typename F, typename T, typename Types>
using reduce2 = typename detail::_reduce2<F, T, Types>::type;

namespace detail {
	template <typename T, typename U>
	struct flatten_reduce_op;

	template <typename... Ts, typename U>
	struct flatten_reduce_op<types<Ts...>, U> {
		using type = types<Ts..., U>;
	};

	template <typename... Ts, typename... Us>
	struct flatten_reduce_op<types<Ts...>, types<Us...>> {
		using type = types<Ts..., Us...>;
	};
}

template <typename T, typename U>
using flatten_reduce_op = typename detail::flatten_reduce_op<T, U>::type;

template <typename L>
using flatten = reduce<flatten_reduce_op, types<>, L>;

namespace detail {

	template <template <typename> typename F>
	struct map_reduce_op {
		template <typename, typename>
		struct inner;

		template <typename... Ts, typename U>
		struct inner<types<Ts...>, U> {
			using type = types<Ts..., F<U>>;
		};
	};
}

template <template <typename> typename F, typename L>
using map = typename reduce2<detail::map_reduce_op<F>::template inner, types<>, L>::type;
