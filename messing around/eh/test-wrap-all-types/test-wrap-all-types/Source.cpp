#include "types.h"

#include <iostream>

struct A {
	int u = 0;
};

auto function_that_refs(Ref<A> a) {
	return a;
}

auto function_that_copies(Value<A> a) {
	return a;
}

auto function_that_matches_any(Ref<A> a) {
	return a;
}

auto function_that_matches_any(Value<A> a) {
	return a;
}

auto function_that_matches_any(Temporary<A> a) {
	return a;
}

int main() {
	{
		// demonstrating that y is a reference to x
		// by assigning, then updating x.u = 1 and printing y.u = 1
		// notice we can call function_that_refs but not function_that_copies
		// but we can call x.copy() to do so

		A a;
		auto x = Ref(a);
		auto y = x;

		x.use().u = 1;
		std::cout << y.use().u << "\n";

		function_that_refs(x);
		//function_that_copies(x); // doesn't compile
		function_that_refs(y);
		//function_that_copies(y); // doesn't compile

		//function_that_copies(x); // doesn't compile
		function_that_copies(x.copy());
		//function_that_copies(y); // doesn't compile
		function_that_copies(y.copy());
	}
	{
		// notice how we can't directly call function_that_copies
		// with a value, we need to explicitly copy or move
		// this is done to avoid mistakenly copying when we thought we were moving

		auto x = Value(A{});
		// function_that_copies(x); // doesn't compile
		function_that_copies(x.move());
		function_that_copies(x.copy());
	}
	{
		// See how we can't accidentally cast to any type
		// we need to decide what we do with the value by calling ref copy or move

		auto x = Value(A{});
		//function_that_matches_any(x); // doesn't compile


		// mouse over in your IDE to see the expected type aliases values
		using expect_ref = decltype(function_that_matches_any(x.reference()));
		using expect_val = decltype(function_that_matches_any(x.copy()));
		using expect_temp = decltype(function_that_matches_any(x.move()));
	}
}
