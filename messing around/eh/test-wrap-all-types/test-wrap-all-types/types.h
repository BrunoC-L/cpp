#pragma once
#include <utility>

template <typename T> class Ref;
template <typename T> class ConstRef;

template <typename T>
Ref<T> ref(T& obj) {
	return Ref<T>(obj);
}

template <typename T>
ConstRef<T> const_ref(const T& obj) {
	return ConstRef<T>(obj);
}

template <typename T>
class Ref {
public:
	Ref(T& obj) : ref(obj) {};
	Ref(const T&) = delete;

	Ref(const Ref&) = default;
	Ref& operator=(const Ref&) = default;
	Ref(Ref&&) = default;
	Ref& operator=(Ref&&) = default;

	T& get() {
		return ref;
	}
	ConstRef<T> get_const() const {
		return const_ref(ref);
	}
	~Ref() = default;
protected:
	T& ref;
};

template <typename T>
class ConstRef {
public:
	ConstRef(T&) = delete;
	ConstRef(const T& obj) : ref(obj) {};

	ConstRef(const ConstRef&) = default;
	ConstRef& operator=(const ConstRef&) = default;
	ConstRef(ConstRef&&) = default;
	ConstRef& operator=(ConstRef&&) = default;

	ConstRef<T> get_const() const {
		return const_ref(ref);
	}
	~ConstRef() = default;
protected:
	T& ref;
};
