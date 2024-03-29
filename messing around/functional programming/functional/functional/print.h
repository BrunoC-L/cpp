#pragma once
#include <string>
#include <iostream>
#include <optional>
#include <utility>
#include <sstream>

namespace print_ns {
	template <typename T, typename = void>
	struct is_iterable : std::false_type {};

	template <typename T>
	struct is_iterable<T, std::void_t<decltype(begin(std::declval<T>())), decltype(end(std::declval<T>()))>> : std::true_type {};

	template <typename T, typename = void>
	struct is_string : std::false_type {};

	template <typename T>
	struct is_string<T, std::void_t<decltype(std::string(std::declval<T>()))>> : std::true_type {};

	template <class T, template <class...> class Template>
	struct is_specialization : std::false_type {};

	template <template <class...> class Template, class... Args>
	struct is_specialization<Template<Args...>, Template> : std::true_type {};

	auto print = [](auto&& t, auto&&... ts) {
		using T = std::remove_const_t<std::remove_reference_t<decltype(t)>>;
		if constexpr (std::is_same_v<T, std::stringstream>) {
			print(t.str());
		}
		else if constexpr (is_iterable<T>::value && !is_string<T>::value) {
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
		else if constexpr (is_specialization<T, std::optional>::value) {
			if (t.has_value()) {
				std::cout << "{ ";
				print(t.value());
				std::cout << " }";
			}
			else
				std::cout << "{}";
		}
		else if constexpr (is_specialization<T, std::pair>::value) {
			std::cout << "{ ";
			print(t.first);
			std::cout << ", ";
			print(t.second);
			std::cout << " }";
		}
		else {
			std::cout << t;
		}
		if constexpr (sizeof... (ts) > 0) {
			std::cout << " ";
			print(std::forward<decltype(ts)>(ts)...);
		}
	};

	auto println = [](auto&&... ts) {
		print(std::forward<decltype(ts)>(ts)..., "\n");
	};
};
