#include "types.h"

namespace my {
	template <typename T>
	struct int_if_single_float_if_list;

	template <typename T>
	struct int_if_single_float_if_list {
		using type = int;
	};

	template <typename... Ts>
	struct int_if_single_float_if_list<types<Ts...>> {
		using type = float;
	};
}

template <typename T>
using F = my::int_if_single_float_if_list<T>::type;

int main() {

	using u = types<types<float, int>, types<void, types<float>>>;
	using v = flatten<u>;

	v c;

	map<F, types<>> v1;
	map<F, types<int>> v2;
	map<F, types<int, int>> v3;
	map<F, types<int, int, types<>>> v4;

	return 0;
}
