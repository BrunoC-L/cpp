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
        return detail::fold(std::move(generator), f, default_value);
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
