#include "types.h"
#include <iostream>

struct A {
	A() {
		std::cout << "Create\n";
	}
	A(const A&) {
		std::cout << "Copy\n";
	}
	A(A&&) {
		std::cout << "Move\n";
	}
	~A() {
		std::cout << "Destroy\n";
	}
};

auto function_that_refs(Ref<A> a) {}

auto function_that_copies(Value<A> a) {}

auto function_that_matches_any(Ref<A> a) {}

auto function_that_matches_any(Value<A> a) {}

auto function_that_matches_any(Temporary<A> a) {}

int main() {
	{
		// notice that with a reference, 
		// we can call function_that_refs but not function_that_copies
		// but we can by calling x.copy() or by calling x.move()
		// which will create a value by moving instead of copying

		A a;
		auto x = Ref(a);
		auto y = x.reference();

		function_that_refs(x.reference());
		//function_that_copies(x); // doesn't compile
		//function_that_copies(x.reference()); // doesn't compile
		function_that_refs(y.reference());
		//function_that_copies(y); // doesn't compile
		//function_that_copies(y.reference()); // doesn't compile

		//function_that_copies(x); // doesn't compile
		function_that_copies(x.copy());
		function_that_copies(x.move());
		//function_that_copies(y); // doesn't compile
		function_that_copies(y.copy());
		function_that_copies(y.move());
	}
	{
		std::cout << "\n";

		// notice how we can't directly call function_that_copies
		// with a value, we need to explicitly copy or move
		// this is done to avoid mistakenly copying when we thought we were moving

		auto x = Value(A{});
		// function_that_copies(x); // doesn't compile
		//function_that_copies(x.move()); // doesn't compile
		function_that_copies(x.copy());
	}
	{
		std::cout << "\n";
		// See how we can't accidentally cast to any type
		// we need to decide what we do with the value by calling ref copy or move

		auto x = Value(A{});
		//function_that_matches_any(x); // doesn't compile
		function_that_matches_any(x.reference());
		function_that_matches_any(x.copy());
		function_that_matches_any(x.move());
	}
}
