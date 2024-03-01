#pragma once
#include <ranges>
#include <tuple>
#include <variant>

template <size_t I, typename It>
struct index_iterator {
	static constexpr size_t i = I;
	It it;
};

template <typename... Ts, std::size_t... I>
auto index_iterator_variants(std::index_sequence<I...>) {
	return std::variant<index_iterator<I, Ts>...>{};
}
template <typename... Ts, typename Indices = std::make_index_sequence<sizeof...(Ts)>>
auto index_iterator_variants() {
	return index_iterator_variants<Ts...>(Indices{});
}

namespace caesium_utility {
	namespace detail {
		template <std::ranges::range... Rs>
		struct range_join;

		template <std::ranges::range R, std::ranges::range... Rs>
		struct range_join_iterator {
			decltype(index_iterator_variants<typename R::iterator, typename Rs::iterator...>()) iterator_variant;
			const range_join<R, Rs...>* ranges_ptr;

			static constexpr size_t size = 1 + sizeof...(Rs);
			using difference_type = int;
			using value_type = R::value_type;

			value_type& operator*() const {
				return std::visit([](const auto& it)->value_type& {
					return *it.it;
				}, iterator_variant);
			}

			bool operator==(const range_join_iterator& other) const {
				if (iterator_variant.index() != other.iterator_variant.index())
					return false;
				return std::visit([&](const auto& it) {
					return it.it == std::get<std::remove_cvref_t<decltype(it)>>(other.iterator_variant).it;
				}, iterator_variant);
			}

			range_join_iterator& operator++() {
				std::visit([&](auto& it) {
					it.it++;
					if constexpr (it.i + 1 < size) {
						if (it.it != std::get<it.i>(ranges_ptr->ranges).get().end())
							return;
						auto next_it = std::get<it.i + 1>(ranges_ptr->ranges).get().begin();
						iterator_variant = index_iterator<it.i + 1, std::remove_reference_t<decltype(next_it)>>{ std::move(next_it) };
					}
				}, iterator_variant);
				return *this;
			}

			void operator++(int) {
				++*this;
			}
		};

		template <std::ranges::range... Rs>
		struct range_join {
			std::tuple<std::reference_wrapper<Rs>...> ranges;
			using iterator = range_join_iterator<Rs...>;

			range_join_iterator<Rs...> begin() const {
				auto it = std::get<0>(ranges).get().begin();
				return { index_iterator<0, std::remove_reference_t<decltype(it)>>{ it }, this };
			}
			range_join_iterator<Rs...> end() const {
				auto it = std::get<sizeof...(Rs) - 1>(ranges).get().end();
				return { index_iterator<sizeof...(Rs) - 1, std::remove_reference_t<decltype(it)>>{ it }, this };
			}
		};
	}

	template <typename... Ts>
	detail::range_join<std::remove_reference_t<Ts>...>
		range_join(Ts&&... ranges) {
		return { std::tuple{ std::reference_wrapper{ ranges }... } };
	}
}
