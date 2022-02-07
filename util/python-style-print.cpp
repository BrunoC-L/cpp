#include <vector>
#include <string>
#include <iostream>
#include <forward_list>

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>> : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T, typename = void>
struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::void_t<decltype(std::string(std::declval<T>()))>> : std::true_type {};

template <typename T>
constexpr bool is_string_v = is_string<T>::value;

auto print = [](auto&& t) {
	if constexpr (is_string_v<decltype(t)>) {
		std::cout << "\"" << t << "\"";
	}
	else if constexpr (is_iterable_v<decltype(t)>) {
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

int main() {
  println(1, "123", "456", std::vector<int>{ 1, 2, 3, 4 }, std::forward_list<std::forward_list<int>>{ std::forward_list<int>{ 5, 6 }, std::forward_list<int>{ 7, 8 } });
  // outputs: `1, "123", "456", [1, 2, 3, 4], [[5, 6], [7, 8]]`
}
