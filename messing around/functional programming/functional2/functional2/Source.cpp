#include <vector>
#include <optional>
#include <utility>
#include <stdexcept>

#include "print.h"

#define NonCopyableNonDefaultConstructible(T) \
T() = delete;\
T& operator=(const T&) = delete;\
T(const T&) = delete;\
T& operator=(T&&) = default;\
T(T&&) = default;

#define NonDefaultConstructible(T) \
T() = delete;\
T& operator=(const T&) = default;\
T(const T&) = default;\
T& operator=(T&&) = default;\
T(T&&) = default;

namespace FunctionTypes {
    struct Sequence {};
    struct Element {};
    struct OptionalElement {};
}

struct IteratorSentinel {};

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

    decltype(auto) operator()(auto it) && {
        return filter_iterator(std::move(f), it);
    }

    decltype(auto) operator()(auto it) & {
        return filter_iterator(f, it);
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
auto get_structure_iterator(T& structure) {
    return structure_iterator(structure.begin(), structure.end());
}

template <typename T, typename Op, typename... Ops>
decltype(auto) op(T& t, Op op1, Ops... ops) {
    if constexpr (sizeof...(ops) == 0)
        return op1(get_structure_iterator(t));
    else
        return op(op1(get_structure_iterator(t)), ops...);
}

int main() {
    using namespace print_ns;

    std::vector<int> v1 = { 1, 2, 3 };

    auto a = filter{ [](auto&& x) {
        return x % 2;
    } };
    auto it1 = get_structure_iterator(v1);
    auto it2 = a(it1);
    auto it3 = get_structure_iterator(it1);
    auto it4 = get_structure_iterator(it2);
    auto it5 = a(it2);
    println(it1);
    println(it2);
    println(it3);
    println(it4);
    println(it5);

    println(op(
        v1,
        filter{ [](auto&& x) { return x % 2; } }
    ));
    return 0;
}
