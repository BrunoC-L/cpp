#include "types.h"
#include <iostream>

constexpr bool printing = false;

struct A {
	static unsigned create_or_copy_count;
	A() {
		if (printing)
			std::cout << "Create\n";
		A::create_or_copy_count += 1;
	}
	A(const A&) {
		if (printing)
			std::cout << "Copy\n";
		A::create_or_copy_count += 1;
	}
	A(A&&) {
		if (printing)
			std::cout << "Move\n";
	}
	~A() {
		if (printing)
			std::cout << "Destroy\n";
	}
};
unsigned A::create_or_copy_count = 0;

auto function_taking_ref(Ref<A> a) {}

auto function_taking_value(Value<A> a) {}

auto function_that_matches_either(Ref<A> a) {}

auto function_that_matches_either(Value<A> a) {}

void expect_count_to_be(unsigned n) {
	if (A::create_or_copy_count != n) {
		std::cout << "Expected count to be " << n << " but was " << A::create_or_copy_count << "\nExiting...\n";
		exit(1);
	}
}

int main() {
	expect_count_to_be(0);
	{
		if (printing)
			std::cout << "1:\n";
		// notice that with a reference, 
		// we can call function_that_refs but not function_that_copies
		// but we can by calling x.copy() or by calling x.move()
		// which will create a value by moving instead of copying

		A a;
		expect_count_to_be(1);
		auto x = ref_of(a);
		auto y = x.ref();

		function_taking_ref(x.ref());
		//function_taking_value(x); // doesn't compile
		//function_taking_value(x.reference()); // doesn't compile
		function_taking_ref(y.ref());
		//function_taking_value(y); // doesn't compile
		//function_taking_value(y.reference()); // doesn't compile

		expect_count_to_be(1);

		//function_taking_value(x); // doesn't compile
		function_taking_value(x.copy());

		expect_count_to_be(2);

		//function_taking_value(y); // doesn't compile
		function_taking_value(y.copy());

		expect_count_to_be(3);
	}
	{
		if (printing)
			std::cout << "\n2:\n";

		// notice how we can't directly call function_that_copies
		// with a value, we need to explicitly copy or move
		// this is done to avoid mistakenly copying when we thought we were moving

		Value<A> x = move_into_value(A{});

		expect_count_to_be(4);

		// function_taking_value(x); // doesn't compile
		function_taking_value(x.move());
		function_taking_value(x.copy());

		expect_count_to_be(5);
	}
	{
		if (printing)
			std::cout << "\n3:\n";
		// See how we can't accidentally cast
		// we need to decide exactly what we do
		// with the value by calling ref copy or move

		Value<A> x = move_into_value(A{});

		expect_count_to_be(6);

		//function_that_matches_either(x); // doesn't compile
		function_that_matches_either(x.ref());
		function_that_matches_either(x.copy());

		expect_count_to_be(7);

		function_that_matches_either(x.move());

		expect_count_to_be(7);
	}
	{
		if (printing)
			std::cout << "\n4:\n";
		Value<A> x1 = move_into_value(A{});
		expect_count_to_be(8);
		Value<A> x2 = copy_into_value(A{});
		expect_count_to_be(10);
	}
}
