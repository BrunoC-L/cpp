#pragma once
#include <tuple>
#include <vector>
#include <variant>
#include <iostream>

template <typename T, template <typename...> typename Template>
struct is_specialization : std::false_type {};

template <template <typename...> typename Template, typename... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

namespace vecview {

	template <typename T>
	concept View = T::value_type;

	template <typename T, typename value_type>
	concept ViewOf = std::is_same_v<typename T::value_type, value_type>;

	template <typename T>
	struct mutable_element_ref {
		T& e;
		using value_type = T;
		using iterator = T*;

		size_t size() const {
			return 1;
		}
	};

	template <typename T>
	struct const_element_ref {
		const T& e;
		using value_type = T;
		using iterator = const T*;

		size_t size() const {
			return 1;
		}
	};

	template <typename T>
	struct element_value {
		T e;
		using value_type = T;
		using iterator = T*;

		size_t size() const {
			return 1;
		}

		bool is_moved = false;
		static constexpr bool DEBUG_PRINTS = false;

		element_value(T&& e) : e(std::move(e)) {
			if constexpr (DEBUG_PRINTS) {
				puts("create");
				std::cout << (int)(this) << "\n";
			}
		}

		element_value(const element_value& other) : e(e) {
			throw;
		}

		element_value(element_value&& other) : e(std::move(other.e)) {
			if constexpr (DEBUG_PRINTS) {
				puts("move");
				std::cout << (int)(this) << "\n";
				other.is_moved = true;
			}
		}

		~element_value() {
			if constexpr (DEBUG_PRINTS) {
				if (is_moved)
					return;
				puts("destroy");
				std::cout << (int)(this) << "\n";
			}
		}
	};

	template <typename T>
	mutable_element_ref<T> element(T& e) {
		return { e };
	}

	template <typename T>
	const_element_ref<T> element(const T& e) {
		return { e };
	}

	template <typename T>
	element_value<T> element(T&& e) {
		return { std::move(e) };
	}

	template <typename T>
	element_value<T> element(const T&& e) = delete;


	//value
	template <typename T>
	T* begin(element_value<T>& e) {
		return &e.e;
	}

	template <typename T>
	const T* begin(const element_value<T>& e) {
		return &e.e;
	}

	template <typename T>
	T* begin(element_value<T>&& e) = delete;

	template <typename T>
	T* end(element_value<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	const T* end(const element_value<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	T* end(element_value<T>&& e) = delete;


	//ref
	template <typename T>
	T* begin(mutable_element_ref<T>& e) {
		return &e.e;
	}

	template <typename T>
	const T* begin(const mutable_element_ref<T>& e) {
		return &e.e;
	}

	template <typename T>
	T* begin(mutable_element_ref<T>&& e) = delete;

	template <typename T>
	T* end(mutable_element_ref<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	const T* end(const mutable_element_ref<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	T* end(mutable_element_ref<T>&& e) = delete;


	//const ref
	template <typename T>
	const T* begin(const_element_ref<T>& e) {
		return &e.e;
	}

	template <typename T>
	const T* begin(const const_element_ref<T>& e) {
		return &e.e;
	}

	template <typename T>
	const T* begin(const_element_ref<T>&& e) = delete;

	template <typename T>
	const T* end(const_element_ref<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	const T* end(const const_element_ref<T>& e) {
		return std::next(&e.e);
	}

	template <typename T>
	const T* end(const_element_ref<T>&& e) = delete;

	template <typename T, typename... Vs>
	struct view_tuple;

	template <typename T, typename... Vs>
	struct mutable_view_tuple_iterator;

	template <typename T>
	struct view_tuple<T> {
		using value_type = T;
		using iterator = mutable_view_tuple_iterator<T>;
		size_t size() const {
			return 0;
		}
	};

	// https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/
	template <std::size_t... Idx> auto make_index_dispatcher(std::index_sequence<Idx...>) { return [](auto&& f) { (f(std::integral_constant<std::size_t, Idx>{}), ...); }; }
	template <std::size_t N> auto make_index_dispatcher() { return make_index_dispatcher(std::make_index_sequence<N>{}); }
	template <typename Tuple, typename Func> void for_each(Tuple&& t, Func&& f) { make_index_dispatcher<std::tuple_size<std::decay_t<Tuple>>::value>()([&f, &t](auto idx) { f(std::get<idx>(std::forward<Tuple>(t))); }); }


	template <typename T, typename V, typename... Vs>
	struct view_tuple<T, V, Vs...> {
		std::tuple<V, Vs...> views;
		using value_type = T;
		using iterator = mutable_view_tuple_iterator<T, V, Vs...>;
		size_t size() const {
			size_t res = 0;
			for_each(views, [&](const auto& view) { res += view.size(); });
			return res;
		}
	};

	template <typename T>
	const T* begin(view_tuple<T>& e) {
		return nullptr;
	}

	template <typename T>
	const T* end(view_tuple<T>& e) {
		return nullptr;
	}

	template <size_t I, typename It>
	struct index_iterator {
		static constexpr size_t i = I;
		It it;
	};

	template <typename... Ts, std::size_t... I>
	std::variant<index_iterator<I, Ts>...> index_iterator_variants(std::index_sequence<I...>) {
		throw;
	}
	template <typename... Ts, typename Indices = std::make_index_sequence<sizeof...(Ts)>>
	auto index_iterator_variants() {
		return index_iterator_variants<Ts...>(Indices{});
	}

	template <typename T, typename V, typename... Vs>
	struct mutable_view_tuple_iterator<T, V, Vs...> {
		std::reference_wrapper<view_tuple<T, V, Vs...>> underlying;
		decltype(index_iterator_variants<typename std::remove_cvref_t<V>::iterator, typename std::remove_cvref_t<Vs>::iterator...>()) iterator_variant;
		size_t cur;
		bool is_end = false;
		static constexpr size_t size = 1 + sizeof...(Vs);
		using difference_type = int;
		using value_type = T;
	};

	template <typename T, typename V, typename... Vs>
	struct mutable_view_tuple_end_sentinel {};

	template <typename T, typename V, typename... Vs>
	bool operator==(const mutable_view_tuple_iterator<T, V, Vs...>& l, const mutable_view_tuple_iterator<T, V, Vs...>& r) {
		if (l.iterator_variant.index() != r.iterator_variant.index())
			return false;
		if (l.is_end)
			return true;
		return std::visit([&](const auto& it) {
			return it.it == std::get<std::remove_cvref_t<decltype(it)>>(r.iterator_variant).it;
		}, l.iterator_variant);
	}

	template <typename T, typename V, typename... Vs>
	bool operator==(const mutable_view_tuple_iterator<T, V, Vs...>& l, const mutable_view_tuple_end_sentinel<T, V, Vs...>&) {
		return l.is_end;
	}

	template <typename T, typename V, typename... Vs>
	T& operator*(mutable_view_tuple_iterator<T, V, Vs...>& it);

	template <typename T, typename V, typename... Vs>
	mutable_view_tuple_iterator<T, V, Vs...>& operator++(mutable_view_tuple_iterator<T, V, Vs...>& _it) {
		if (_it.is_end)
			abort();
		std::visit([&](auto& it) -> void {
			++it.it;
			if (it.it != end(std::get<it.i>(_it.underlying.get().views)))
				return;
			if constexpr (it.i + 1 < _it.size) {
				auto next_it = begin(std::get<it.i + 1>(_it.underlying.get().views));
				_it.iterator_variant = index_iterator<it.i + 1, std::remove_reference_t<decltype(next_it)>>{ std::move(next_it) };
			}
			else
				_it.is_end = true;
		}, _it.iterator_variant);
		return _it;
	}

	template <typename T, typename V, typename... Vs>
	T& operator*(mutable_view_tuple_iterator<T, V, Vs...>& it) {
		return std::visit([](auto& it)-> T& {
			return *it.it;
		}, it.iterator_variant);
	}

	template <typename T, typename V, typename... Vs>
	mutable_view_tuple_iterator<T, V, Vs...> begin(view_tuple<T, V, Vs...>& e) {
		auto& first_view = std::get<0>(e.views);
		return { e, index_iterator<0, decltype(begin(std::get<0>(e.views)))>{ begin(first_view) }};
	}

	template <typename T, typename V, typename... Vs>
	mutable_view_tuple_end_sentinel<T, V, Vs...> end(const view_tuple<T, V, Vs...>& e) {
		return {};
	}

	/*template <typename T>
	view_tuple<T> join() {
		return {};
	}*/

	template <typename T>
	struct remove_rvalue;

	template <typename T>
	struct remove_rvalue<T&> {
		using type = T&;
	};

	template <typename T>
	struct remove_rvalue<T&&> {
		using type = T;
	};

	template <typename T, typename... Ts>
	view_tuple<typename std::remove_cvref_t<T>::value_type, typename remove_rvalue<T&&>::type, typename remove_rvalue<Ts&&>::type...> join(T&& t, Ts&&... ts) {
		return { std::tuple<typename remove_rvalue<T&&>::type, typename remove_rvalue<Ts&&>::type...>{ std::forward<decltype(t)>(t), std::forward<decltype(ts)>(ts)...} };
	}
}
