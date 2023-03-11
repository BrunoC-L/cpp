#pragma once
#include <utility>
#include "int.h"
#include "pair.h"

namespace types {

	using int_ns::Int;
	using namespace int_ns::named_values;
	using pair::Pair;

	template <typename...>
	struct Types;

	namespace _Get {
		template <typename T, typename Index>
		struct Get;

		template <typename T, typename... Ts>
		struct Get<Types<T, Ts...>, Zero> {
			using type = T;
		};

		template <typename Index, typename T, typename... Ts>
		struct Get<Types<T, Ts...>, Index> {
			using type = typename Get<Types<Ts...>, typename Index::template Minus<One>>::type;
		};

		// called with any container L, dispatch to Get<Types...>
		// to avoid L<Ts...> not defined for L<T, Ts...> such as L = Pair
		template <template <typename...> typename L, typename Index, typename... Ts>
		struct Get<L<Ts...>, Index> {
			using type = Get<Types<Ts...>, Index>::type;
		};
	}

	template <typename T, typename Index>
	using Get = typename _Get::Get<T, Index>::type;

	namespace _Join {
		template <typename T, typename U>
		struct Join;

		template <template <typename...> typename L, typename... Ts, typename... Us>
		struct Join<L<Ts...>, L<Us...>> {
			using type = L<Ts..., Us...>;
		};
	}

	template <typename T, typename U>
	using Join = typename _Join::Join<T, U>::type;

	namespace _IndexOf {
		template <typename T, typename E>
		struct IndexOf;

		template <template <typename...> typename L, typename T, typename... Ts, typename E>
		struct IndexOf<L<T, Ts...>, E> {
			using type = Int<1>::Plus<typename IndexOf<L<Ts...>, E>::type>;
		};

		template <template <typename...> typename L, typename... Ts, typename E>
		struct IndexOf<L<E, Ts...>, E> {
			using type = Int<0>;
		};
	}

	template <typename T, typename E>
	using IndexOf = typename _IndexOf::IndexOf<T, E>::type;

	namespace _Contains {
		template <typename T, typename E>
		struct Contains;

		template <template <typename...> typename L, typename T, typename... Ts, typename E>
		struct Contains<L<T, Ts...>, E> {
			using type = typename Contains<L<Ts...>, E>::type;
		};

		template <template <typename...> typename L, typename... Ts, typename E>
		struct Contains<L<E, Ts...>, E> {
			using type = std::true_type;
		};

		template <template <typename...> typename L, typename E>
		struct Contains<L<>, E> {
			using type = std::false_type;
		};
	}

	template <typename T, typename E>
	using Contains = typename _Contains::Contains<T, E>::type;

	namespace _Reverse {
		template <typename T, typename U>
		struct ReverseInto;

		template <template <typename...> typename L, typename T, typename... Ts, typename... Us>
		struct ReverseInto<L<T, Ts...>, L<Us...>> {
			using next = L<T, Us...>;
			using type = typename ReverseInto<L<Ts...>, next>::type;
		};

		template <template <typename...> typename L, typename U>
		struct ReverseInto<L<>, U> {
			using type = U;
		};

		template <typename T>
		struct Reverse;

		template <template <typename...> typename L, typename... Ts>
		struct Reverse<L<Ts...>> {
			using type = typename ReverseInto<L<Ts...>, L<>>::type;
		};
	}

	template <typename... Ts>
	using Reverse = typename _Reverse::Reverse<Ts...>::type;

	namespace _Head {

		template <typename T>
		struct Head;

		template <template <typename...> typename L, typename T, typename... Ts>
		struct Head<L<T, Ts...>> {
			using type = T;
		};

		template <template <typename...> typename L>
		struct Head<L<>> {
			using type = struct {};
		};
	}

	template <typename T>
	using Head = typename _Head::Head<T>::type;

	template <typename T>
	using Tail = typename _Head::Head<typename T::Reverse>::type;

	namespace _Index {
		template <typename T, typename U>
		struct IndexInto;

		template <template <typename...> typename L, typename T, typename... Ts, typename... Us>
		struct IndexInto<L<T, Ts...>, L<Us...>> {
			using next = L<Us..., Pair<typename L<Us...>::Size, T>>;
			using type = typename IndexInto<L<Ts...>, next>::type;
		};

		template <template <typename...> typename L, typename U>
		struct IndexInto<L<>, U> {
			using type = U;
		};
	}

	template <typename T>
	using Index = typename _Index::IndexInto<T, Types<>>::type;

	namespace _SplitAtIndices {
		template <typename T, typename Index, typename U>
		struct SplitAtIndexInto;

		template <template <typename...> typename L, typename T, typename... Ts, typename Index, typename... Us>
		struct SplitAtIndexInto<L<T, Ts...>, Index, L<Us...>> {
			using type = typename SplitAtIndexInto<L<Ts...>, typename Index::template Minus<One>, L<Us..., T>>::type;
		};

		// need path with 0 and T, Ts... otherwise it can't choose between specializing priority with 0 (below) or T, Ts... (above)
		template <template <typename...> typename L, typename T, typename... Ts, typename... Us>
		struct SplitAtIndexInto<L<T, Ts...>, Int<0>, L<Us...>> {
			using type = L<L<Us...>, L<T, Ts...>>;
		};

		template <template <typename...> typename L, typename... Ts, typename... Us>
		struct SplitAtIndexInto<L<Ts...>, Int<0>, L<Us...>> {
			using type = L<L<Us...>, L<Ts...>>;
		};

		template <typename T, typename Indices, typename U>
		struct SplitAtIndicesInto;

		template <template <typename...> typename L, typename T, typename Index, typename... Indices, typename U>
		struct SplitAtIndicesInto<T, L<Index, Indices...>, U> {
			using SplitAtIndex = T::template SplitAtIndex<Index>;
			using Take = typename SplitAtIndex::template Get<Int<0>>;
			using Remain = typename SplitAtIndex::template Get<Int<1>>;
			using newU = typename U::template Join<L<Take>>;
			using type = SplitAtIndicesInto<Remain, L<Indices...>, newU>;
		};

		template <template <typename...> typename L, typename T, typename U>
		struct SplitAtIndicesInto<T, L<>, U> {
			using type = U;
		};
	}

	template <typename T, typename Index>
	using SplitAtIndex = typename _SplitAtIndices::SplitAtIndexInto<T, Index, Types<>>::type;

	template <typename T, typename Indices>
	using SplitAtIndices = typename _SplitAtIndices::SplitAtIndicesInto<T, Indices, Types<>>::type;

	template <typename... Ts>
	struct Types {

		using type = Types<Ts...>;

		using Size = Int<sizeof...(Ts)>;

		using Reverse = Reverse<type>;

		using Index = Index<type>;

		using Head = Head<type>;

		using Tail = Tail<type>;

		template <typename Index>
		using Get = Get<type, Index>;

		template <typename T>
		using Join = Join<type, T>;

		template <typename E>
		using IndexOf = IndexOf<type, E>;

		template <typename E>
		using Contains = Contains<type, E>;

		template <typename Index>
		using SplitAtIndex = SplitAtIndex<type, Index>;

		template <typename Indices>
		using SplitAtIndices = SplitAtIndices<type, Indices>;
	};
}
