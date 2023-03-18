#include "types.h"
#include <iostream>
#include "use-cases.h"
#include <vector>

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
	// const references extend the lifetime of rvalues
	// this has nothing to do specifically with the 3 reference types, it is very useful to keep in mind
	// example initalizing ConstRef with a SomeType&&
	ConstRef(SomeType{});
	// this means that if you store const references without copying, there is a
	// chance that as soon as you store and return from the function
	// the reference is invalidated as the rvalue is destroyed.
	// this is absolutely crucial to keep in mind in order to avoid headaches
	// so never store without copying like so
	{
		std::vector<SomeType> v;
		v.push_back(ConstRef(SomeType{}).copy());
	}

	// Call functions safely, as the three reference types never
	// implicitly convert to eachother, example:
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
	// difference between a temporary or a reference
	// but in practice, temporary are meant to be std::move(...)'d
	// and references are not.
	// By "meant to" it is implied that the last call in the stack with a temporary
	// argument makes use of the fact that is it a temporary and moves it
	// otherwise it would have been simpler for everyone to just use a reference
	// by simpler, it is meant that if for example you have a reference and a function requires a temporary
	// you will have to copy, but if that same function required a reference you wouldn't have to copy
	// so do not ask for a temporary if you don't need one

	// to move the value referenced by a Temporary, you can either
	std::move(tref.use()); /*or */ tref.move();

	// and every reference type allow to copy the referenced value
	ref.copy();
	cref.copy();
	tref.copy();
}

int main() {
	example();
	use_cases();
}
