#pragma once
#include "detail.h"

#define NonCopyableNonDefaultConstructible(T)\
T() = delete;\
T& operator=(const T&) = delete;\
T(const T&) = delete;\
T& operator=(T&&) = default;\
T(T&&) = default;

template <typename Operation>
concept FunctionalOperation = requires(Operation) {
    typename Operation::InputType;
};

template <typename F>
struct map {
    F f;

    constexpr map(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(map);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::map(std::move(generator), f);
    }
};

template <typename F>
struct filter {
    F f;

    constexpr filter(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(filter);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::filter(std::move(generator), std::move(f));
    }
};

template <typename F, typename D>
struct fold {
    F f;
    D default_value;

    constexpr fold(F&& f, D&& d) : f(std::move(f)), default_value(std::move(d)) {}
    NonCopyableNonDefaultConstructible(fold);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::fold(std::move(generator), std::move(f), std::move(default_value));
    }
};

template <typename FBefore, typename FDuring, typename FAfter, typename D>
struct complex_fold {
    FBefore f_before;
    FDuring f_during;
    FAfter f_after;
    D default_value;

    constexpr complex_fold(
        FBefore f_before,
        FDuring f_during,
        FAfter f_after,
        D d
    ) : f_before(std::move(f_before)),
        f_during(std::move(f_during)),
        f_after(std::move(f_after)),
        default_value(std::move(d)) {}
    NonCopyableNonDefaultConstructible(complex_fold);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;
    
    constexpr auto operator()(auto generator) && {
        return detail::complex_fold(
            std::move(generator),
            std::move(f_before),
            std::move(f_during),
            std::move(f_after),
            std::move(default_value));
    }
};

template <typename F, typename D>
    requires std::is_same<std::invoke_result_t<F, D, D>, std::optional<D>>::value
struct partial_fold {
    F f;
    D default_value;

    constexpr partial_fold(F&& f, D&& d) : f(std::move(f)), default_value(std::move(d)) {}
    NonCopyableNonDefaultConstructible(partial_fold);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::partial_fold(std::move(generator), std::move(f), std::move(default_value));
    }
};

template <typename F>
struct apply {
    F f;

    constexpr apply(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(apply);

    using InputType = FunctionTypes::Element;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::apply(std::move(generator), std::move(f));
    }
};

template <typename F>
struct find {
    F f;

    constexpr find(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(find);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) & = delete;

    constexpr auto operator()(auto generator) && {
        return detail::find(std::move(generator), std::move(f));
    }
};

template <typename F>
struct partial_filter {
    F f;

    constexpr partial_filter(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(partial_filter);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::partial_filter(std::move(generator), std::move(f));
    }
};

template <typename F>
struct foreach {
    F f;

    constexpr foreach(F&& f) : f(std::move(f)) {}
    NonCopyableNonDefaultConstructible(foreach);

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::foreach(std::move(generator), std::move(f));
    }
};

auto g(auto generator, FunctionalOperation auto op, FunctionalOperation auto... operators) {
    if constexpr (sizeof...(operators) == 0)
        return std::move(op)(detail::identity_gen<decltype(op)::InputType>(std::move(generator)));
    else
        return g(std::move(op)(detail::identity_gen<decltype(op)::InputType>(std::move(generator))), std::forward<decltype(operators)>(operators)...);
}

auto op(auto operand, FunctionalOperation auto... operators) {
    if constexpr (sizeof...(operators) == 0)
        return operand;
    else
        return detail::collect(g(detail::identity_element(std::move(operand)), std::forward<decltype(operators)>(operators)...));
}
