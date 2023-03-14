#pragma once
#include <utility>

template <typename T> class Ref;
template <typename T> class Value;
template <typename T> class Temporary;

template <typename T>
auto ref_of(T& v) {
	return Ref<T>::of(v);
}

template <typename T>
auto move_into_value(T&& v) {
	return Value<T>::of_moved(std::move(v));
}

template <typename T>
auto copy_into_value(const T& v) {
	return Value<T>::of_copy(v);
}

template <typename T>
class Ref {
public:
	static Ref of(T& v) {
		return Ref<T>(v);
	}
	
	Ref(Ref&&) = default;
	~Ref() = default;

	T& use() {
		return v;
	}

	Value<T> copy() {
		return copy_into_value(v);
	}

	Ref<T> ref() {
		return ref_of(v);
	}

protected:
	Ref(T& v) : v(v) {};
	T& v;
};

template <typename T>
class Value {
public:
	static Value of_copy(const T& v) {
		return Value(v);
	}

	static Value of_moved(T&& v) {
		return Value(std::move(v));
	}

	Value(Value&&) = default;
	~Value() = default;

	T& use() {
		return v;
	}

	Value<T> copy() {
		return Value(v);
	}

	Value<T> move() {
		return Value(std::move(v));
	}

	Ref<T> ref() {
		return ref_of(v);
	}

protected:
	Value(T&& v) : v(std::move(v)) {};
	Value(const T& v) : v(v) {};
	T v;
};
