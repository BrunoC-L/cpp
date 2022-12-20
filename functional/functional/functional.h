#pragma once
#include "detail.h"

template <typename Operation>
concept FunctionalOperation = requires(Operation) {
    typename Operation::InputType;
    typename Operation::OutputType;
};

template <typename F>
struct map {
    F f;

    using InputType = FunctionTypes::Sequence;
    using OutputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        using G = raw_t<decltype(generator)>;
        using O = typename G::OutputType;
        if constexpr (std::is_same_v<InputType, O>)
            return detail::map(std::move(generator), f);
        else
            return detail::map(detail::identity_seq_gen(std::move(generator)), f);
    }
};

template <typename F>
struct filter {
    F f;

    using InputType = FunctionTypes::Sequence;
    using OutputType = FunctionTypes::Sequence;

    constexpr auto operator()(auto generator) {
        return detail::filter(std::move(generator), f);
    }
};

template <typename F, typename D>
struct fold {
    F f;
    D default_value;

    using InputType = FunctionTypes::Sequence;
    using OutputType = FunctionTypes::Element;

    constexpr auto operator()(auto generator) {
        return detail::fold(std::move(generator), f, default_value);
    }
};

template <typename F>
struct apply {
    F f;

    using InputType = FunctionTypes::Element;
    using OutputType = FunctionTypes::Element;

    constexpr auto operator()(auto generator) {
        using G = raw_t<decltype(generator)>;
        return detail::apply(std::move(generator), f);
    }
};

auto g(auto generator, FunctionalOperation auto op, FunctionalOperation auto... operators) {
    using InputType = raw_t<decltype(op)>::InputType;
    if constexpr (std::is_same<InputType, FunctionTypes::Sequence>::value) {
        auto temp = detail::identity_seq_gen(std::move(generator));
        if constexpr (sizeof...(operators) == 0)
            return op(std::move(temp));
        else
            return g(op(std::move(temp)), std::forward<decltype(operators)>(operators)...);
    }
    else {
        auto temp = detail::identity_element_gen(std::move(generator));
        if constexpr (sizeof...(operators) == 0)
            return op(std::move(temp));
        else
            return g(op(std::move(temp)), std::forward<decltype(operators)>(operators)...);
    }
}

auto op(auto operand, FunctionalOperation auto... operators) {
    if constexpr (sizeof...(operators) == 0)
        return std::move(operand);
    else {
        using InputType = typename Head<decltype(operators)...>::type::InputType;
        if constexpr (std::is_same<InputType, FunctionTypes::Sequence>::value) {
            auto generator = g(detail::identity_seq(std::move(operand)), std::forward<decltype(operators)>(operators)...);
            using OutputType = typename Tail<decltype(operators)...>::type::OutputType;
            if constexpr (std::is_same<OutputType, FunctionTypes::Sequence>::value)
                return detail::collect_sequence(std::move(generator));
            else if constexpr (std::is_same<OutputType, FunctionTypes::Element>::value)
                return detail::collect_element(std::move(generator));
            else
                static_assert(!sizeof(OutputType*));
        }
        else {
            auto generator = g(detail::identity_element(std::move(operand)), std::forward<decltype(operators)>(operators)...);
            using OutputType = typename Tail<decltype(operators)...>::type::OutputType;
            if constexpr (std::is_same<OutputType, FunctionTypes::Sequence>::value)
                return detail::collect_sequence(std::move(generator));
            else if constexpr (std::is_same<OutputType, FunctionTypes::Element>::value)
                return detail::collect_element(std::move(generator));
            else
                static_assert(!sizeof(OutputType*));
        }
        
    }
}
