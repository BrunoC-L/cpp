#pragma once
#include "functional.h"
#include "print.h"
#include <unordered_map>

namespace futil {

	namespace collectors {
		template <typename T, typename U>
		const auto tomap = fold{ [](auto m, std::pair<T, U> next) {
			m[next.first] = next.second;
			return m;
		}, std::unordered_map<T, U>{} };
	}

	namespace folds {
		constexpr auto sum = fold{ [](auto a, auto b) { return a + b; }, int{0} };
		constexpr auto sum_with_starting_value = [](auto starting_value) {
			return fold{ [](auto a, auto b) { return a + b; }, starting_value };
		};
		constexpr auto mul = fold{ [](auto a, auto b) { return a * b; }, int{1} };
		constexpr auto mul_with_starting_value = [](auto starting_value) {
			return fold{ [](auto a, auto b) { return a + b; }, starting_value };
		};
	}

	namespace conversions {
		namespace functions {
			constexpr auto to_string = [](auto x) -> std::string {
				if constexpr (std::is_same_v<std::remove_cvref_t<decltype(x)>, std::string>)
					return x;
				else
					return std::to_string(x);
			};
		}
		namespace applications {
			constexpr auto to_string = apply{ functions::to_string };
		}
		namespace maps {
			constexpr auto to_string =  map{ functions::to_string };
		}
	}

	namespace manipulations {
		namespace maps {
			constexpr auto index_from = [](int beg) {
				return map{ [i = beg](auto x) mutable -> std::pair<int, decltype(x)> {
					return std::pair{ i++, x };
				} };
			};
			constexpr auto index_from_zero = map{ [i = 0](auto x) mutable -> std::pair<int, decltype(x)> {
					return std::pair{ i++, x };
				} };
			constexpr auto reverse_index_from = [](int beg) {
				return map{ [i = beg](auto x) mutable -> std::pair<int, decltype(x)> {
					return std::pair{ i--, x };
				} };
			};
		}
	}
}
