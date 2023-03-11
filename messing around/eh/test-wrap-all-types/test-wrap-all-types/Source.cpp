#include "types.h"

#include <iostream>

struct A {
	A() {
		std::cout << "A()\n";
	}
	~A() {
		std::cout << "~A()\n";
	}
};

void function_that_refs(Ref<A> a) {

}

void function_that_copies(Ref<A> a) {
	A b = a.get();
}

int main() {
	A a;
	auto x = ref(a);

	function_that_refs(x);
	function_that_copies(x);
}
