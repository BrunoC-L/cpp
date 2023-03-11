#include <iostream>
#include <utility>

void f(auto& left) {
	std::cout << "left\n";
}

void f(const auto& left) {
	std::cout << "const left\n";
}

void f(auto&& universal) {
	std::cout << "universal\n";
}

void g(auto& left) {
	std::cout << "left\n";
}

void g(auto&& universal) {
	std::cout << "universal\n";
}

template <typename T>
struct hold_whatever {
	T t;
};

int main() {
	{
		int i = 1;
		const int j = 1;

		f(i); // prints left
		f(j); // prints const left
		f(1); // prints universal
		f(std::move(i)); // prints universal
		f(std::move(j)); // prints universal (with a warning about moving a const variable)
	}
	{
		int i = 1;
		const int j = 1;

		g(i); // prints left
		g(j); // prints left (decltype(left) -> const int)
		g(1); // prints universal
		g(std::move(i)); // prints universal
		g(std::move(j)); // prints universal (with a warning about moving a const variable)
	}
	{
		int i = 1;

		// commented = doesn't compie

		// tests with 1
		auto x1 = hold_whatever{ 1 }; // t is int
	//  auto x2 = hold_whatever<int&>{ 1 };
		auto x3 = hold_whatever<const int&>{ 1 };
		auto x4 = hold_whatever<int&&>{ 1 }; // t is int&&
		auto x5 = hold_whatever<const int&&>{ 1 }; // t is int const &&

		// tests with i
		auto y1 = hold_whatever{ i }; // t is int
		auto y2 = hold_whatever<int&>{ i }; // t is int&
		auto y3 = hold_whatever<const int&>{ i }; // t is int const &
	//  auto y4 = hold_whatever<int&&>{ i };
	//  auto y5 = hold_whatever<const int&&>{ i };

		// tests with move(i)
		auto z1 = hold_whatever{ std::move(i) }; // t is int
	//  auto z2 = hold_whatever<int&>{ std::move(i) };
		auto z3 = hold_whatever<const int&>{ std::move(i) };
		auto z4 = hold_whatever<int&&>{ std::move(i) }; // t is int&&
		auto z5 = hold_whatever<const int&&>{ std::move(i) }; // t is int const &&

		// x1.t is just 'int'
		static_assert(std::is_same_v<int, decltype(x1.t)>);

		// if it was anything else we would know
		static_assert(!std::is_same_v<const int, decltype(x1.t)>);
		static_assert(!std::is_same_v<int&, decltype(x1.t)>);
		static_assert(!std::is_same_v<int&&, decltype(x1.t)>);
		static_assert(!std::is_same_v<const int&, decltype(x1.t)>);
		static_assert(!std::is_same_v<const int&&, decltype(x1.t)>);

		// all other types
		static_assert(std::is_same_v<int, decltype(x1.t)>);
		static_assert(std::is_same_v<const int&, decltype(x3.t)>);
		static_assert(std::is_same_v<int&&, decltype(x4.t)>);
		static_assert(std::is_same_v<const int&&, decltype(x5.t)>);

		static_assert(std::is_same_v<int, decltype(y1.t)>);
		static_assert(std::is_same_v<int&, decltype(y2.t)>);
		static_assert(std::is_same_v<const int&, decltype(y3.t)>);

		static_assert(std::is_same_v<int, decltype(z1.t)>);
		static_assert(std::is_same_v<const int&, decltype(z3.t)>);
		static_assert(std::is_same_v<int&&, decltype(z4.t)>);
		static_assert(std::is_same_v<const int&&, decltype(z5.t)>);

		return 0;
	}
}
