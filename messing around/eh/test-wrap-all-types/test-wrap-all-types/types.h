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

	const T& use() const {
		return v;
	}

	T copy() const {
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

	T copy() const {
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

	T copy() const {
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

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <typename T>
concept AnyReference = std::disjunction_v<is_specialization<T, Ref>, is_specialization<T, ConstRef>, is_specialization<T, Temporary>>;

template <typename T>
concept NonTemporary = std::disjunction_v<is_specialization<T, Ref>, is_specialization<T, ConstRef>>;

template <template <class...> class T1, template <class...> class T2>
struct is_same_template : std::false_type {};

template <template <class...> class T1>
struct is_same_template<T1, T1> : std::true_type {};

template <template <typename> typename T>
concept AnyReferenceTemplate = std::disjunction_v<is_same_template<T, Ref>, is_same_template<T, ConstRef>, is_same_template<T, Temporary>>;

template <template <typename> typename T>
concept NonTemporaryTemplate = std::disjunction_v<is_same_template<T, Ref>, is_same_template<T, ConstRef>>;
