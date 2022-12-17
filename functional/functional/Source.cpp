#include <iostream>
#include <vector>
#include <optional>
#include <variant>

#include "print.h"

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <typename T>
struct filter_t {
	using value_type = T;
	std::optional<T> opt;
};

//template <class T, class... Args>
//using is_specialization_rm_ref = is_specialization<std::remove_reference_t<T>, Args...>;

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
	if constexpr (isMap) {
		return f(element);
	}
	else if constexpr (isFilter) {
		return element;
	}
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply_through(auto&& element, auto&& f, auto&&... fs) {
	throw std::runtime_error("do not call unless in decltype(apply_through(...))");
	constexpr bool isMap = is_specialization<std::remove_reference_t<decltype(f)>, map>::value;
	constexpr bool isFilter = is_specialization<std::remove_reference_t<decltype(f)>, filter>::value;
	if constexpr (isMap) {
		return apply_through(f(element), fs...);
	}
	else if constexpr (isFilter) {
		return apply_through(element, fs...);
	}
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply(auto&& element, auto&& f) {
	constexpr bool isMap = is_specialization<std::remove_reference_t<decltype(f)>, map>::value;
	constexpr bool isFilter = is_specialization<std::remove_reference_t<decltype(f)>, filter>::value;
	using E = std::remove_const_t<std::remove_reference_t<decltype(element)>>;
	constexpr bool is_filter_t = is_specialization<E, filter_t>::value;

	if constexpr (isMap && !is_filter_t) {
		return f(element);
	}
	else if constexpr (isMap && is_filter_t) {
		using Inner = E::value_type;
		using Next = std::remove_const_t<std::remove_reference_t<decltype(f(element.opt.value()))>>;
		return filter_t<Next>{
			element.opt.has_value() ?
				std::optional(f(element.opt.value())) :
				std::nullopt
		};
	}
	else if constexpr (isFilter && !is_filter_t) {
		return f(element) ? filter_t{ std::optional(element) } : filter_t<E>{ {} };
	}
	else if constexpr (isFilter && is_filter_t) {
		using Inner = E::value_type;
		return element.opt.has_value() && f(element.opt.value()) ? filter_t<Inner>{ element.opt } : filter_t<Inner>{ {} };
	}
	else
		static_assert(!sizeof(decltype(f)*), "error");
}

auto apply(auto&& element, auto&& f, auto&&... fs) {
	using E = std::remove_const_t<std::remove_reference_t<decltype(element)>>;
	constexpr bool is_filter_t = is_specialization<E, filter_t>::value;
	using Next = std::remove_const_t<std::remove_reference_t<decltype(apply(apply(element, f), fs...))>>;
	if constexpr (is_filter_t)
		if (!element.opt.has_value())
			return Next{ {} };
	return apply(apply(element, f), fs...);
}

auto op(auto&& container, auto&&... fs) {
	if constexpr (sizeof...(fs) == 0)
		return container;
	else {
		using T = std::remove_reference_t<decltype(apply_through(container.at(0), fs...))>;
		using U = std::remove_reference_t<decltype(apply(container.at(0), fs...))>;
		std::vector<T> res;
		res.reserve(container.size());
		if constexpr (is_specialization<U, filter_t>::value) {
			for (const auto& e : container) {
				auto v = apply(e, fs...);
				if (v.opt.has_value())
					res.emplace_back(std::move(v.opt.value()));
			}
		}
		else {
			for (const auto& e : container)
				res.push_back(apply(e, fs...));
		}
		return res;
	}
}

auto compose = [](auto&& f, auto&&... fs) {
	if constexpr (sizeof...(fs) == 0)
		return [=](auto... params) { return f(params...); };
	else
		return [=](auto... params) { return compose(fs...)(f(params...)); };
};


int main() {
	auto x = apply(1, map{ [](int x) { return x + 1; } });
	auto y = apply(1, filter{ [](int x) { return x - 1; } }, map{ [](int x) { return x + 1; } });
	auto z = apply(1, filter{ [](int x) { return x + 1; } }, filter{ [](int x) { return x + 1; } });
	auto u = apply(1, map{ [](int x) { return x + 1; } }, map{ [](int x) { return x + 1; } });
	auto x2 = apply(1,
		map{ [](auto&& x) { return x + 1; } },
		map{ [](auto&& x) { return x + 1; } },
		filter{ [](auto&& x) { return x != 1; } });
	auto x3 = apply(1,
		map{
			compose(
				[](auto&& x) { return x + 1; },
				[](auto&& x) { return std::to_string(x); }
			)
		}
	);
	auto x4 = apply(1,
		map{ [](auto&& x) { return x + 1; } },
		map{ [](auto&& x) { return std::to_string(x); } }
	);

	auto v1 = std::vector{ 1, 2, 3, 4 };
	println(v1);
	auto v2 = op(v1,
		map{ [](auto&& x) { return x + 1; } },
		filter{ [](auto&& x) { return x > 1; } },
		map{ [](auto&& x) { return x + 1; } },
		map{ [](auto&& x) { return x + 1; } },
		filter{ [](auto&& x) { return x > 1; } },
		map{ [](auto&& x) { return x + 1; } },
		filter{ [](auto&& x) { return x > 1; } },
		map{ [](auto&& x) { return std::to_string(x); } });
	println(v2);

	return 0;
}
