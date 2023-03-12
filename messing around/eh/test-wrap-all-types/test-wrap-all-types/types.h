#pragma once
#include <utility>

template <typename T> class Ref;
template <typename T> class Value;
template <typename T> class Temporary;

template <typename T>
class Ref {
public:
	Ref(T& v) : v(v) {};

	Ref(const Ref&) = default;
	Ref& operator=(const Ref&) = delete;
	~Ref() = default;

	T& use() {
		return v;
	}

	Value<T> copy() {
		return Value(v);
	}

	Temporary<T> move() {
		return Temporary(std::move(v));
	}

	Ref<T> reference() {
		return *this;
	}

protected:
	T& v;
};

template <typename T>
class Value {
public:
	Value(T&& v) : v(std::move(v)) {};
	Value(const T& v) : v(v) {};

	Value(Value&& v) : v(std::move(v.v)) {};
	Value(const Value&) = delete;
	Value& operator=(const Value&) = delete;
	Value& operator=(Temporary<T>&& other) { v = std::move(other.v); };

	T& use() {
		return v;
	}

	Value<T> copy() {
		return Value(v);
	}

	Temporary<T> move() {
		return Temporary(std::move(v));
	}

	Ref<T> reference() {
		return Ref(v);
	}

	~Value() = default;
protected:
	T v;
};

template <typename T>
class Temporary {
public:
	Temporary(T&& v) : v(std::move(v)) {};

	Temporary(Temporary& v) : v(std::move(v.v)) {};
	Temporary& operator=(const Temporary&) = delete;

	T& use() {
		return v;
	}

	Value<T> copy() {
		return Value(std::move(v));
	}

	Temporary<T> move() {
		return Temporary(std::move(v));
	}

	Ref<T> reference() {
		return Ref(v);
	}

	operator Value<T>() {
		return copy();
	}

	~Temporary() = default;
protected:
	T v;
};
