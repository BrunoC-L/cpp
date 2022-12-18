#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <variant>

#include "print.h"
#include "helper.h"

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <typename T>
struct filter_t {
	using value_type = T;
	std::optional<T> opt;
};

template<typename T>
struct raw {
	using type = std::remove_const_t<std::remove_reference_t<T>>;
};

template <typename T>
using raw_t = raw<T>::type;

template <typename F>
struct map {
	F f;
	decltype(auto) operator()(auto&&... args) {
		return f(args...);
	}
};

template <typename F>
struct filter {
	F f;
	decltype(auto) operator()(auto&&... args) {
		return f(args...);
	}
};

auto apply_through(auto&& element, auto&& f) {
	throw std::runtime_error("do not call unless in decltype(apply_through(...))");
	constexpr bool isMap = is_specialization<std::remove_reference_t<decltype(f)>, map>::value;
	constexpr bool isFilter = is_specialization<std::remove_reference_t<decltype(f)>, filter>::value;
	if constexpr (isMap)
		return f(element);
	else if constexpr (isFilter)
		return element;
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply_through(auto&& element, auto&& f, auto&&... fs) {
	throw std::runtime_error("do not call unless in decltype(apply_through(...))");
	constexpr bool isMap = is_specialization<std::remove_reference_t<decltype(f)>, map>::value;
	constexpr bool isFilter = is_specialization<std::remove_reference_t<decltype(f)>, filter>::value;
	if constexpr (isMap)
		return apply_through(f(element), fs...);
	else if constexpr (isFilter)
		return apply_through(element, fs...);
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply(auto&& element, auto&& f) {
	constexpr bool isMap = is_specialization<std::remove_reference_t<decltype(f)>, map>::value;
	constexpr bool isFilter = is_specialization<std::remove_reference_t<decltype(f)>, filter>::value;
	using E = raw_t<decltype(element)>;
	constexpr bool is_filter_t = is_specialization<E, filter_t>::value;

	if constexpr (isMap && !is_filter_t)
		return f(element);
	else if constexpr (isMap && is_filter_t)
		return filter_t<raw_t<decltype(f(element.opt.value()))>>{
			element.opt.has_value() ?
				std::optional(f(element.opt.value())) :
				std::nullopt
		};
	else if constexpr (isFilter && !is_filter_t)
		return f(element) ? filter_t{ std::optional(element) } : filter_t<E>{ {} };
	else if constexpr (isFilter && is_filter_t)
		return element.opt.has_value() && f(element.opt.value()) ? filter_t<E::value_type>{ element.opt } : filter_t<E::value_type>{ {} };
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply(auto&& element, auto&& f, auto&&... fs) {
	using E = raw_t<decltype(element)>;
	constexpr bool is_filter_t = is_specialization<E, filter_t>::value;
	using Next = raw_t<decltype(apply(apply(element, f), fs...))>;
	if constexpr (is_filter_t)
		if (!element.opt.has_value())
			return Next{ {} };
	return apply(apply(element, f), fs...);
}

auto op(auto&& operand, auto&&... fs) {
	if constexpr (sizeof...(fs) == 0)
		return operand;
	else {
		using T = raw_t<decltype(apply_through(operand.at(0), fs...))>;
		using U = raw_t<decltype(apply(operand.at(0), fs...))>;
		std::vector<T> res;
		res.reserve(operand.size());
		if constexpr (is_specialization<U, filter_t>::value)
			for (const auto& e : operand) {
				auto v = apply(e, fs...);
				if (v.opt.has_value())
					res.emplace_back(std::move(v.opt.value()));
			}
		else
			for (const auto& e : operand)
				res.push_back(apply(e, fs...));
		return res;
	}
}

auto compose(auto&& f, auto&&... fs) {
	if constexpr (sizeof...(fs) == 0)
		return [=](auto&&... params) { return f(params...); };
	else
		return [=](auto&&... params) { return compose(fs...)(f(params...)); };
};

template <typename F>
struct MAP {
	F f;
	decltype(auto) operator()(auto&&... args) {
		return f(args...);
	}
};

template <typename F>
struct FILTER {
	F f;
	bool operator()(auto&&... args) {
		return f(args...);
	}
};

template <typename F>
struct FOLD {
	F f;
	bool operator()(auto&&... args) {
		return f(args...);
	}
};

//template <typename... Ts>
//struct FOLDGroup;
//
//template <typename... Ts>
//struct MAPFILTERGroup;
//
//template <>
//struct MAPFILTERGroup<> {};
//
//template <typename T, typename... Ts>
//struct MAPFILTERGroup<T, Ts...> {
//	T first;
//	MAPFILTERGroup<Ts...> next;
//};
//template <typename T, typename... Ts>
//struct FOLDGroup<T, Ts...> {
//	T first;
//	MAPFILTERGroup<Ts...> next;
//};
//
//template <typename OP>
//concept MapFilter = is_specialization<OP, MAP>::value || is_specialization<OP, FILTER>::value;
//
//template <typename OP>
//concept Reduction = is_specialization<OP, FOLD>::value;
//
//template <typename T, typename... Ts>
//	requires Reduction<T>
//FOLDGroup<T, Ts...> constexpr group(T t, Ts... ts);
//
//template <typename T, typename... Ts>
//	requires MapFilter<T>
//MAPFILTERGroup<T, Ts...> constexpr group(T t, Ts... ts) {
//	if constexpr (sizeof...(ts) == 0)
//		return { t, {} };
//	else
//		return {
//			t,
//			group(ts...)
//	};
//}
//
//template <typename T, typename... Ts>
//	requires Reduction<T>
//FOLDGroup<T, Ts...> constexpr group(T t, Ts... ts) {
//	if constexpr (sizeof...(ts) == 0)
//		return { t, {} };
//	else
//		return {
//			t,
//			group(ts...)
//	};
//}

template <typename... Ts>
struct Group;

template <>
struct Group<> {};

template <typename T, typename... Ts>
struct Group<T, Ts...> {
	T first;
	Group<Ts...> next;
};

template <typename T, typename... Ts>
Group<T, Ts...> group(T t, Ts... ts) {
	if constexpr (sizeof...(ts) == 0)
		return { t, {} };
	else
		return { t, group(ts...) };
}

int main() {
	auto tuple = std::make_tuple<std::string, std::array<int, 3>, char>("S", {1, 2, 3}, 'c');
	auto reversed = as_tuple_reversed("S", std::array<int, 3>{ 1, 2, 3 }, 'c');

	auto f = [](auto first, std::array<int, 3> second, auto third) {
		std::cout << first << ", " << "[" << second[0] << ", " << second[1] << ", " << second[2] << "]" << ", " << third << "\n";
	};

	call_from_tuple(f, tuple);
	call_from_tuple_reverse(f, tuple);
	auto compositeObj1 = group(
		MAP{ 1 },
		MAP{ 2 }
	);
	return 0;

	//auto x = apply(1, map{ [](int x) { return x + 1; } });
	//auto y = apply(1, filter{ [](int x) { return x - 1; } }, map{ [](int x) { return x + 1; } });
	//auto z = apply(1, filter{ [](int x) { return x + 1; } }, filter{ [](int x) { return x + 1; } });
	//auto u = apply(1, map{ [](int x) { return x + 1; } }, map{ [](int x) { return x + 1; } });
	//auto x2 = apply(1,
	//	map{ [](auto&& x) { return x + 1; } },
	//	map{ [](auto&& x) { return x + 1; } },
	//	filter{ [](auto&& x) { return x != 1; } });
	//auto x3 = apply(1,
	//	map{
	//		compose(
	//			[](auto&& x) { return x + 1; },
	//			[](auto&& x) { return std::to_string(x); }
	//		)
	//	}
	//);
	//auto x4 = apply(1,
	//	map{ [](auto&& x) { return x + 1; } },
	//	map{ [](auto&& x) { return std::to_string(x); } }
	//);

	//auto v1 = std::vector{ 1, 2, 3, 4 };
	//println(v1);
	//auto v2 = op(v1,
	//	map{ [](auto&& x) { return x + 1; } },
	//	filter{ [](auto&& x) { return x > 1; } },
	//	map{ [](auto&& x) { return x + 1; } },
	//	map{ [](auto&& x) { return x + 1; } },
	//	filter{ [](auto&& x) { return x > 1; } },
	//	map{ [](auto&& x) { return x + 1; } },
	//	filter{ [](auto&& x) { return x > 1; } },
	//	map{ [](auto&& x) { return std::to_string(x); } });
	//println(v2);

	//return 0;
}
