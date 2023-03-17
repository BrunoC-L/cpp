#include "types.h"
#include <iostream>
#include "use-cases.h"

struct SomeType {};

auto function_taking_ref(Ref<SomeType> a) {}

auto function_that_matches_either_c_or_t(ConstRef<SomeType> a) {}

auto function_that_matches_either_c_or_t(Temporary<SomeType> a) {}

void example() {
	// Three Reference types exist in this system
	// Their use in terms of deciding which type to take as a function parameter is as such:
	// 1. Const Reference : indicates a need to read from the object
	// 2. Reference       : indicates a need to write to the object, but not move it
	// 3. Temporary       : indicates a need to move the object, to store it for example

	// First, create a value
	SomeType a; 
	// Then create one of the tree reference types from the value:
	auto cref = ConstRef(a);
	auto ref = Ref(a);
	auto tref = Temporary(a);
	// technically you can also do this because const references extend the lifetime of rvalues
	auto another_cref = ConstRef(SomeType{});

	// then call functions safely, as the three reference types never implicitly convert
	// example:
	function_taking_ref(ref);
	function_that_matches_either_c_or_t(cref);
	function_that_matches_either_c_or_t(tref);

	// Ref and Temporary are convertible to ConstRef since it is more restrictive (no write allowed)
	ref.const_ref();
	tref.const_ref();
	// Temporary is convertible to Ref since it is more restrictive (no move allowed)
	tref.ref();

	// each reference offers the .use() method
	cref.use();
	ref.use();
	tref.use();

	// "use" returns the referenced value, in theory there is no
	// difference between calling use on a temporary or on a reference
	// but in practice, temporary are meant to be std::move(...)'d
	// and references are not.
	// By "meant to" it is implied that the last call in the stack with a temporary
	// argument makes use of the fact that is it a temporary and moves it
	// otherwise it would have been simpler for everyone to just use a reference

	// to move the value referenced by a Temporary, you can either
	std::move(tref.use()); /*or */ tref.move();

	// and to copy a referenced value
	ref.copy();
	cref.copy();
	tref.copy();

	// copying is sometimes necessary, for example if you
	// want to call a function that requires a temporary but you have a reference
	// this can happen often as taking references is more versatile but
	// you should consider writing 2 variants of the function when you can, 1 taking ref and 1 temp
	// but anyway if all you have is a ref and you need a temp, copy the value and create a temp from it
}


int main() {
	example();
	use_cases();
}
