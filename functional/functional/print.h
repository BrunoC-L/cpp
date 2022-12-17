#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <forward_list>

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>> : std::true_type {};

template <typename T, typename = void>
struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::void_t<decltype(std::string(std::declval<T>()))>> : std::true_type {};

auto print = [](auto&& t) {
	if constexpr (is_string<decltype(t)>::value) {
		std::cout << "\"" << t << "\"";
	}
	else if constexpr (is_iterable<decltype(t)>::value) {
		std::cout << "[";
		bool hasPrevious = false;
		for (const auto& e : t) {
			if (hasPrevious)
				std::cout << ", ";
			hasPrevious = true;
			print(e);
		}
		std::cout << "]";
	}
	else {
		std::cout << t;
	}
};

auto print2 = [](auto&& t, auto&&... ts) {
	print(t);
	if constexpr (sizeof... (ts) > 0) {
		std::cout << ", ";
		print2(ts...);
	}
};

auto println = [](auto&& t, auto&&... ts) {
	print2(t, ts...);
	std::cout << "\n";
};
