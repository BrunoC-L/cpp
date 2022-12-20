#pragma once
#include "generator.h"
#include <vector>

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <typename T>
using raw_t = std::remove_const_t<std::remove_reference_t<T>>;

template <typename T, typename...>
struct Head {
    using type = T;
};

template <typename... Ts>
struct Tail;

template <typename T>
struct Tail<T> {
    using type = T;
};

template <typename T, typename... Ts>
struct Tail<T, Ts...> {
    using type = Tail<Ts...>::type;
};

namespace FunctionTypes {
    struct Sequence {};
    struct Element {};
    struct PartialSequence {};
    struct OptionalElement {};
}

namespace detail {
    template <typename value_type>
    std::vector<value_type> collect_sequence(Generator<value_type, FunctionTypes::Sequence>&& seq) {
        std::vector<value_type> res;
        while (seq)
            res.push_back(seq());
        return res;
    }
    template <typename value_type>
    value_type collect_element(Generator<value_type, FunctionTypes::Element>&& seq) {
        return seq();
    }

    template <typename T>
    Generator<T, FunctionTypes::Element> identity_element(T t) {
        co_yield(t);
    }

    template <typename T>
    Generator<T, FunctionTypes::Element> identity_element_gen(Generator<T, FunctionTypes::Element> gen) {
        co_yield(gen());
    }

    template <typename T>
    Generator<std::vector<T>, FunctionTypes::Element> identity_element_gen(Generator<T, FunctionTypes::Sequence> gen) {
        std::vector<T> res;
        while (gen)
            res.push_back(gen());
        co_yield(res);
    }

    template <typename Seq>
    Generator<typename Seq::value_type, FunctionTypes::Sequence> identity_seq(Seq seq) {
        for (auto& e : seq)
            co_yield(e);
    }

    template <typename T>
    Generator<T, FunctionTypes::Sequence> identity_seq_gen(Generator<T, FunctionTypes::Sequence> gen) {
        while (gen)
            co_yield(gen());
    }

    template <typename T>
    Generator<typename T::value_type, FunctionTypes::Sequence> identity_seq_gen(Generator<T, FunctionTypes::Element> gen) {
        for (auto& e : gen())
            co_yield(e);
    }

    template <typename T, typename F>
    Generator<std::invoke_result_t<F, T>, FunctionTypes::Sequence> map(Generator<T, FunctionTypes::Sequence> gen, F f) {
        while (gen)
            co_yield(f(gen()));
    }

    template <typename T, typename F>
    Generator<std::invoke_result_t<F, T>, FunctionTypes::Sequence> map(Generator<T, FunctionTypes::Element> gen, F f) {
        for (auto& e : gen())
            co_yield(f(e));
    }

    template <typename T, typename F>
    Generator<std::invoke_result_t<F, T>, FunctionTypes::Element> apply(Generator<T, FunctionTypes::Element> gen, F f) {
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
}
