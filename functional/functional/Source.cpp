#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <variant>
#include <coroutine>
#include <exception>
#include <unordered_map>
#include "print.h"

int counter = 0;
int handlecounter = 0;
std::unordered_map<void*, int> handlemap = {};

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <typename T>
using raw_t = std::remove_const_t<std::remove_reference_t<T>>;

template <typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    using value_type = T;
    int myval = 0;

    Generator(const Generator<T>&) = delete;
    Generator<T>& operator=(const Generator<T>&) = delete;
    Generator(Generator<T>&& other) {
        *this = std::move(other);
        std::cout << "moved " << myval << " \n";
    }
    Generator<T>& operator=(Generator<T>&& other) {
        myval = other.myval;
        std::cout << "moving " << myval << " \n";
        h_ = other.h_;
        other.h_ = {};
        full_ = other.full_;
        other.full_ = false;
        return *this;
    }

    struct promise_type // required
    {
        T value_{};
        std::exception_ptr exception_{};

        Generator get_return_object() {
            return Generator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() {
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        void unhandled_exception() {
            exception_ = std::current_exception();
        }

        template <std::convertible_to<T> From>
        std::suspend_always yield_value(From&& from) {
            value_ = std::forward<From>(from);
            return {};
        }
        void return_void() { }
    };

    handle_type h_;

    Generator(handle_type h): h_(h) {
        myval = ++counter;
        handlemap[h_.address()] = ++handlecounter;
        std::cout << "using      " << handlemap[h_.address()] << " from coroutine " << myval << "\n";
    }

    ~Generator() {
        if (h_.address()) {// will be nullptr after move
            std::cout << "destroying " << handlemap[h_.address()] << " from coroutine " << myval << "\n";
            h_.destroy();
            h_ = {};
        }
        else {
            std::cout << "releasing moved         temporary " << myval << "\n";
        }
    }
    explicit operator bool() {
        std::cout << "accessing  " << handlemap[h_.address()] << " from coroutine " << myval << "\n";
        fill();
        return !h_.done();
    }
    T operator()() {
        fill();
        full_ = false;
        return std::move(h_.promise().value_);
    }

private:
    bool full_ = false;

    void fill() {
        if (!full_) {
            h_();
            if (h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            full_ = true;
        }
    }
};

namespace detail {
    template <typename value_type>
    Generator<value_type> identity_from_sequence(auto seq) {
        for (auto& e : seq)
            co_yield(e);
    }

    template <typename value_type>
    Generator<value_type> identity_from_generator(auto seq) {
        while (seq)
            co_yield(seq());
    }

    template <typename value_type, typename result_type>
    Generator<result_type> not_identity_from_sequence(auto seq, auto f) {
        for (auto& e : seq)
            co_yield(f(e));
    }

    template <typename value_type, typename result_type>
    Generator<result_type> not_identity_from_generator(auto seq, auto f) {
        while (seq)
            co_yield(f(seq()));
    }

    template <typename value_type>
    std::vector<value_type> collect(Generator<value_type>& seq) {
        std::vector<value_type> res;
        while (seq)
            res.push_back(seq());
        return res;
    }

    template <typename value_type>
    std::vector<value_type> collect(Generator<value_type>&& seq) {
        std::vector<value_type> res;
        while (seq)
            res.push_back(seq());
        return res;
    }
}

template <typename Container>
auto identity(Container seq) {
    if constexpr (is_specialization<raw_t<Container>, Generator>::value)
        return detail::identity_from_generator<raw_t<Container>::value_type>(std::move(seq));
    else
        return detail::identity_from_sequence<raw_t<Container>::value_type>(std::move(seq));
}

template <typename Container>
auto not_identity(Container&& seq, auto&& f) {
    using T = raw_t<Container>::value_type;
    using R = raw_t<std::invoke_result_t<decltype(f), T>>;
    if constexpr (is_specialization<raw_t<Container>, Generator>::value)
        return detail::not_identity_from_generator<T, R>(
            std::forward<Container>(seq),
            std::forward<decltype(f)>(f)
        );
    else
        return detail::not_identity_from_sequence<T, R>(
            std::forward<Container>(seq),
            std::forward<decltype(f)>(f)
        );
}

template <typename F>
struct map {
    F f;

    map(F&& f): f(f) {

    }

    map(const map<F>&) = delete;
    map<F>& operator=(const map<F>&) = delete;
    map(map<F>&&) = default;
    map<F>& operator=(map<F>&& other) = default;

    constexpr auto operator()(auto&& generator) {
        using T = raw_t<decltype(generator)>::value_type;
        using R = std::invoke_result_t<F, T>;
        return detail::not_identity_from_generator<T, R>(std::move(generator), f);
    }
};

//template <typename F>
//struct filter {
//    F f;
//    constexpr bool operator()(auto&& operand) {
//        return f(std::forward<decltype(operand)>(operand));
//    }
//};
//
//template <typename F>
//struct fold {
//    F f;
//    template <typename T>
//    constexpr T&& operator()(T&& previous, T&& current) {
//        return f(std::forward<T>(previous), std::forward<T>(current));
//    }
//};

template <typename T>
auto g(auto&& generator, map<T> op, auto... operators) {
    if constexpr (sizeof...(operators) == 0) {
        return op(std::move(generator));
    }
    else {
        return g(op(std::forward<decltype(generator)>(generator)), std::forward<decltype(operators)>(operators)...);
    }
}

auto f(auto&& operand, auto&&... operators) {
    if constexpr (sizeof...(operators) == 0) {
        std::cout << "why?\n";
        return operand;
    }
    else {
        auto temp = g(identity(std::forward<decltype(operand)>(operand)), std::forward<decltype(operators)>(operators)...);
        auto res = detail::collect<int>(temp);
        return std::move(res);
    }
        
}

int main() {
    std::vector<int> v1 = { 1, 2, 3 };
    println(v1);
    auto v2 = detail::collect(identity(v1));
    println(v2);
    auto v3 = detail::collect(not_identity(v1, [](auto x) { return std::to_string(x); }));
    println(v3);
    auto v4 = detail::collect(detail::identity_from_generator<int>(
        identity(v1)
    ));
    println(v4);
    auto v5 = detail::collect(detail::not_identity_from_generator<int, int>(
        identity(v1),
        [](auto x) { return -x; }
    ));
    println(v5);

    auto v6 = f(v1, map{ [](auto x) { return -x; } });
    println(v6);

    auto v7 = detail::collect(
        not_identity(
            not_identity(v1, [](auto x) { return std::to_string(x); }),
            [](auto x) { return std::atoi(x.c_str()); }
        )
    );
    println(v7);

    auto v8 = detail::collect(
        not_identity(
            not_identity(identity(v1), [](auto x) { return std::to_string(x); }),
            [](auto x) { return std::atoi(x.c_str()); }
        )
    );
    println(v8);

    auto v0 = f(v1, map{ [](auto x) { return -x; } }, map{ [](auto x) { return 2 * x; } });
    println(v0);
    return 0;
}
