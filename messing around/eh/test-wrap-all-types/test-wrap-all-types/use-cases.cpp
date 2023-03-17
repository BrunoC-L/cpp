#include "types.h"
#include <vector>

struct A {
	int x = 0;
	bool operator==(const A& other) const {
		return other.x == x;
	}
};

// we want to store inside vec so we need a temporary value and a write allowed reference to vec
template <typename T>
auto push_back(Ref<std::vector<T>> vec, Temporary<T> val) {
	vec.use().push_back(std::move(val.use()));
}

// we only want to read the value and the vector so take const references
template <typename T>
auto contains(ConstRef<std::vector<T>> vec, ConstRef<T> val) {
	return std::find(vec.use().begin(), vec.use().end(), val.use()) != vec.use().end();
}

void use_cases() {
	{
		std::vector<A> v;
		A a;
		if (!contains(ConstRef(v), ConstRef(a)))
			push_back(Ref(v), Temporary(a));
	}
}
