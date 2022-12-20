#pragma once
#include "generator.h"
#include <vector>

namespace FunctionTypes {
    struct Sequence {};
    struct Element {};
    struct PartialSequence {};
    struct OptionalElement {};
}

namespace detail {
    // Two types of collectors
    template <typename value_type>
    std::vector<value_type> collect(Generator<value_type, FunctionTypes::Sequence>&& seq) {
        std::vector<value_type> res;
        while (seq)
            res.push_back(seq());
        return res;
    }

    template <typename value_type>
    value_type collect(Generator<value_type, FunctionTypes::Element>&& seq) {
        return seq();
    }

    template <typename T>
    Generator<T, FunctionTypes::Element> identity_element(T t) {
        co_yield(t);
    }

    // Conversions between element and sequence generators
    template <typename T>
    Generator<T, FunctionTypes::Element> identity_element_gen(Generator<T, FunctionTypes::Element> gen) {
        return gen;
    }

    template <typename T>
    Generator<T, FunctionTypes::Sequence> identity_seq_gen(Generator<T, FunctionTypes::Sequence> gen) {
        return gen;
    }

    template <typename T>
    Generator<std::vector<T>, FunctionTypes::Element> identity_element_gen(Generator<T, FunctionTypes::Sequence> gen) {
        std::vector<T> res;
        while (gen)
            res.push_back(gen());
        co_yield(res);
    }

    template <typename T>
    Generator<typename T::value_type, FunctionTypes::Sequence> identity_seq_gen(Generator<T, FunctionTypes::Element> gen) {
        for (auto& e : gen())
            co_yield(e);
    }

    template <typename Target>
    auto identity_gen(auto gen) {
        if constexpr (std::is_same_v<Target, FunctionTypes::Sequence>)
            return identity_seq_gen(std::move(gen));
        else
            return identity_element_gen(std::move(gen));
    }

    template <typename T, typename F>
    Generator<std::invoke_result_t<F, T>, FunctionTypes::Sequence> map(Generator<T, FunctionTypes::Sequence> gen, F f) {
        while (gen)
            co_yield(f(gen()));
    }

    template <typename T>
    Generator<T, FunctionTypes::Sequence> filter(Generator<T, FunctionTypes::Sequence> gen, auto f) {
        while (gen) {
            auto e = gen();
            if (f(e))
                co_yield(e);
        }
    }

    template <typename T, typename U>
    Generator<U, FunctionTypes::Element> fold(Generator<T, FunctionTypes::Sequence> gen, auto f, U default_value) {
        while (gen) {
            auto e = gen();
            default_value = f(default_value, e);
        }
        co_yield(default_value);
    }

    template <typename T, typename F>
    Generator<std::invoke_result_t<F, T>, FunctionTypes::Element> apply(Generator<T, FunctionTypes::Element> gen, F f) {
        co_yield(f(gen()));
    }
}
