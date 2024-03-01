#include <ranges>
#include <vector>
#include "Header.h"
#include <charconv>

template <std::ranges::range T>
static int sum_range(T r) {
	int res = 0;
	for (int& i : r)
		res += i;
	return res;
}

int main() {
	std::vector<int> v1{ 1,2,3 };
	std::vector<int> v2{ 7,8,9 };
	sum_range(v1);

	const auto j = caesium_utility::range_join(v1, v2, v2, v1, v2);
	const auto x = sum_range(j);
	{
		_ASSERT(x == 6 + 24 + 24 + 6 + 24);

		std::array<char, 5> str{ '\0' };
		std::to_chars(str.data(), str.data() + str.size(), x);
		puts(str.data());
	}

	const auto h = caesium_utility::range_join(v1, v2, j, v1, v2);
	const auto y = sum_range(h);
	{
		_ASSERT(y == 6 + 24 + x + 6 + 24);

		std::array<char, 5> str{ '\0' };
		std::to_chars(str.data(), str.data() + str.size(), y);
		puts(str.data());
	}

	return 0;
}
