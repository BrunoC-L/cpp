#pragma once
#include "detail.h"

template <typename Operation>
concept FunctionalOperation = requires(Operation) {
    typename Operation::InputType;
};

template <typename F>
struct map {
    F f;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::map(std::move(generator), f);
    }
};

template <typename F>
struct filter {
    F f;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::filter(std::move(generator), f);
    }
};

template <typename F, typename D>
struct fold {
    F f;
    D default_value;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::fold(std::move(generator), f, std::move(default_value));
    }
};

template <typename FBefore, typename FDuring, typename FAfter, typename D>
struct complex_fold {
    FBefore f_before;
    FDuring f_during;
    FAfter f_after;
    D default_value;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::complex_fold(std::move(generator), f_before, f_during, f_after, std::move(default_value));
    }
};

template <typename F, typename D>
    requires std::is_same<std::invoke_result_t<F, D, D>, std::optional<D>>::value
struct partial_fold {
    F f;
    D default_value;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::partial_fold(std::move(generator), f, std::move(default_value));
    }
};

template <typename F>
struct apply {
    F f;

    using InputType = FunctionTypes::Element;

    constexpr auto operator()(auto generator) {
        return detail::apply(std::move(generator), f);
    }
};

template <typename F>
struct find {
    F f;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::find(std::move(generator), f);
    }
};

template <typename F>
struct partial_filter {
    F f;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::partial_filter(std::move(generator), f);
    }
};

template <typename F>
struct foreach {
    F f;

    using InputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::foreach(std::move(generator), f);
    }
};

auto g(auto generator, FunctionalOperation auto op, FunctionalOperation auto... operators) {
    if constexpr (sizeof...(operators) == 0)
        return op(detail::identity_gen<decltype(op)::InputType>(std::move(generator)));
    else
        return g(op(detail::identity_gen<decltype(op)::InputType>(std::move(generator))), std::forward<decltype(operators)>(operators)...);
}

auto op(auto operand, FunctionalOperation auto... operators) {
    if constexpr (sizeof...(operators) == 0)
        return std::move(operand);
    else
        return detail::collect(g(detail::identity_element(std::move(operand)), std::forward<decltype(operators)>(operators)...));
}
