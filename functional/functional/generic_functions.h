#pragma once
#include "functional.h"
#include "print.h"
#include <unordered_map>

namespace futil {

	namespace collectors {
		constexpr auto tomap = apply{ [](auto gen) {
			return std::unordered_map<int,int>{};
			//return std::unordered_map m(gen);
		} };
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
				int i = beg;
				return map{ [&i](auto x) -> std::pair<int, decltype(x)> {
					return std::pair<unsigned, decltype(x)>{ i++, x };
				} };
			};
			constexpr auto index_from_zero = []() {
				int i = 0;
				return map{ [&i](auto x) -> std::pair<int, decltype(x)> {
					return std::pair<int, decltype(x)>{ i++, x };
				} };
			};
			constexpr auto reverse_index_from = [](int beg) {
				int i = beg;
				return map{ [&i](auto x) -> std::pair<int, decltype(x)> {
					return std::pair<unsigned, decltype(x)>{ i--, x };
				} };
			};
		}
	}
}
