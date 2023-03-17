#pragma once
#include <utility>

template <typename T> class ConstRef;
template <typename T> class Ref;
template <typename T> class Temporary;

template <typename T>
class ConstRef {
public:
	ConstRef(const T& v) : v(v) {};
	ConstRef(ConstRef&&) = default;
	ConstRef(const ConstRef&) = default;
	~ConstRef() = default;

	const T& use() {
		return v;
	}

	T copy() {
		return v;
	}

protected:
	const T& v;
};

template <typename T>
class Ref {
public:
	Ref(T& v) : v(v) {};
	Ref(Ref&&) = default;
	Ref(const Ref&) = default;
	~Ref() = default;

	T& use() {
		return v;
	}

	T copy() {
		return v;
	}

	ConstRef<T> const_ref() {
		return ConstRef(v);
	}
protected:
	T& v;
};

template <typename T>
class Temporary {
public:
	Temporary(T& v) : v(v) {};
	Temporary(Temporary&&) = default;
	Temporary(const Temporary&) = default;
	~Temporary() = default;

	T& use() {
		return v;
	}

	T copy() {
		return v;
	}

	T&& move() {
		return std::move(v);
	}

	Ref<T> ref() {
		return Ref(v);
	}

	ConstRef<T> const_ref() {
		return ConstRef(v);
	}
protected:
	T& v;
};
