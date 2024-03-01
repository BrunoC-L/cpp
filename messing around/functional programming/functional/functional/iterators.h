#pragma once
#include <vector>
#include <optional>
#include <utility>
#include <stdexcept>
#include "detail.h"
#include "print.h"

namespace iterators {
    struct IteratorSentinel {};

    template <typename Operation>
    concept FunctionalOperation = requires(Operation) {
        typename Operation::InputType;
    };

    template <typename F, typename IT>
    struct filter_iterator {
        F f;
        IT it;

        constexpr filter_iterator(F&& f, IT it) : f(std::move(f)), it(it) {}
        constexpr filter_iterator(const F& f, IT it) : f(f), it(it) {}
        NonDefaultConstructible(filter_iterator);

        explicit operator bool() {
            if (it && f(*it))
                return true;
            else {
                operator++();
                if (it && f(*it))
                    return true;
                else
                    return false;
            }
        }

        decltype(auto) operator*() {
            if (operator bool())
                return *it;
            else {
                std::string msg = "";
                throw std::out_of_range(msg);
            }
        }

        decltype(auto) operator++() {
            if (!it)
                return *this;
            it++;
            while (true)
                if (!it || f(*it))
                    return *this;
                else {
                    it++;
                    return *this;
                }
        }

        decltype(auto) operator++(int) {
            return this->operator++();
        }

        bool operator==(const IteratorSentinel&) {
            return !operator bool();
        }

        decltype(auto) begin() {
            return *this;
        }

        decltype(auto) end() {
            return IteratorSentinel{};
        }
    };

    template <typename... Ts>
    decltype(auto) begin(filter_iterator<Ts...> it) {
        return it.begin();
    }

    template <typename... Ts>
    decltype(auto) end(filter_iterator<Ts...> it) {
        return it.end();
    }

    template <typename F>
    struct filter {
        F f;

        constexpr filter(F&& f) : f(std::move(f)) {}
        NonCopyableNonDefaultConstructible(filter);

        using InputType = FunctionTypes::Sequence;

        decltype(auto) operator()(auto it)&& {
            return filter_iterator(std::move(f), it);
        }

        decltype(auto) operator()(auto it)& {
            return filter_iterator(f, it);
        }
    };

    template <typename IT>
    struct take_iterator {
        unsigned n;
        unsigned i = 0;
        IT it;

        constexpr take_iterator(auto n, IT it) : n(n), it(it) {}
        NonDefaultConstructible(take_iterator);

        explicit operator bool() {
            return it && i < n;
        }

        decltype(auto) operator*() {
            if (operator bool())
                return *it;
            else {
                std::string msg = "";
                throw std::out_of_range(msg);
            }
        }

        decltype(auto) operator++() {
            if (!it)
                return *this;
            i++;
            it++;
            return *this;
        }

        decltype(auto) operator++(int) {
            return this->operator++();
        }

        bool operator==(const IteratorSentinel&) {
            return !operator bool();
        }

        decltype(auto) begin() {
            return *this;
        }

        decltype(auto) end() {
            return IteratorSentinel{};
        }
    };

    template <typename... Ts>
    decltype(auto) begin(take_iterator<Ts...> it) {
        return it.begin();
    }

    template <typename... Ts>
    decltype(auto) end(take_iterator<Ts...> it) {
        return it.end();
    }

    struct take {
        unsigned n;

        constexpr take(auto n) : n(n) {}
        NonCopyableNonDefaultConstructible(take);

        using InputType = FunctionTypes::Sequence;

        decltype(auto) operator()(auto it) {
            return take_iterator(n, it);
        }

    };

    template <typename IT, typename END>
    struct structure_iterator {
        IT it;
        END _end;

        explicit operator bool() const noexcept {
            return const_cast<IT&>(it) != _end;
        }

        decltype(auto) operator*() {
            return *it;
        }

        decltype(auto) operator++() {
            it++;
            return *this;
        }

        decltype(auto) operator++(int) {
            it++;
            return *this;
        }

        bool operator==(const IteratorSentinel&) const noexcept {
            return !operator bool();
        }

        decltype(auto) begin() {
            return *this;
        }

        decltype(auto) end() {
            return IteratorSentinel{};
        }
    };

    template <typename... Ts>
    decltype(auto) begin(structure_iterator<Ts...> it) {
        return it.begin();
    }

    template <typename... Ts>
    decltype(auto) end(structure_iterator<Ts...> it) {
        return it.end();
    }

    template <typename T>
    auto get_structure_iterator(T&& structure) {
        return structure_iterator(structure.begin(), structure.end());
    }

    template <typename T, typename Op, typename... Ops>
    decltype(auto) op(T& t, Op op1, Ops... ops) {
        if constexpr (sizeof...(ops) == 0)
            return op1(get_structure_iterator(t));
        else
            return op(op1(get_structure_iterator(t)), ops...);
    }

    /*auto g(auto&& iterator, FunctionalOperation auto op, FunctionalOperation auto... operators) {
        if constexpr (sizeof...(operators) == 0)
            return std::move(op)(detail::identity_gen<decltype(op)::InputType>(std::move(iterator)));
        else
            return g(std::move(op)(detail::identity_gen<decltype(op)::InputType>(std::move(iterator))), std::forward<decltype(operators)>(operators)...);
    }

    auto op(auto&& operand, FunctionalOperation auto&&... operators) {
        if constexpr (sizeof...(operators) == 0)
            return operand;
        else
            return detail::collect(g(get_structure_iterator(std::move(operand)), std::forward<decltype(operators)>(operators)...));
    }*/
}