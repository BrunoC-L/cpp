//#pragma once
//#include <utility>
//
//namespace iterators2 {
//    struct IteratorSentinel {};
//
//    #define NonCopyableNonDefaultConstructible(T)\
//    T() = delete;\
//    T& operator=(const T&) = delete;\
//    T(const T&) = delete;\
//    T& operator=(T&&) = default;\
//    T(T&&) = default;
//
//    #define NonDefaultConstructible(T) \
//    T() = delete;\
//    T& operator=(const T&) = default;\
//    T(const T&) = default;\
//    T& operator=(T&&) = default;\
//    T(T&&) = default;
//
//    namespace FunctionTypes {
//        struct Sequence2 { using Seq = int; };
//        struct Element {};
//        struct OptionalElement {};
//    }
//
//
//    template <typename Operation>
//    concept FunctionalOperation = requires(Operation) {
//        typename Operation::InputType;
//    };
//
//    template <typename IT, typename END>
//    struct structure_iterator {
//        IT it;
//        END _end;
//
//        explicit operator bool() const noexcept {
//            return const_cast<IT&>(it) != _end;
//        }
//
//        decltype(auto) operator*() {
//            return *it;
//        }
//
//        decltype(auto) operator++() {
//            it++;
//            return *this;
//        }
//
//        decltype(auto) operator++(int) {
//            it++;
//            return *this;
//        }
//
//        bool operator==(const IteratorSentinel&) const noexcept {
//            return !operator bool();
//        }
//
//        decltype(auto) begin() {
//            return *this;
//        }
//
//        decltype(auto) end() {
//            return IteratorSentinel{};
//        }
//    };
//
//    template <typename F, typename IT>
//    struct filter_iterator2 {
//        F f;
//        IT it;
//
//        using InputType = FunctionTypes::Sequence2;
//        static constexpr auto InputType2 = FunctionTypes::Sequence2{};
//
//        constexpr filter_iterator2(F&& f, IT it) : f(std::move(f)), it(it) {}
//        constexpr filter_iterator2(const F& f, IT it) : f(f), it(it) {}
//        NonDefaultConstructible(filter_iterator2);
//
//        explicit operator bool() {
//            if (it && f(*it))
//                return true;
//            else {
//                operator++();
//                if (it && f(*it))
//                    return true;
//                else
//                    return false;
//            }
//        }
//
//        decltype(auto) operator*() {
//            if (operator bool())
//                return *it;
//            else {
//                std::string msg = "";
//                throw std::out_of_range(msg);
//            }
//        }
//
//        decltype(auto) operator++() {
//            if (!it)
//                return *this;
//            it++;
//            while (true)
//                if (!it || f(*it))
//                    return *this;
//                else {
//                    it++;
//                    return *this;
//                }
//        }
//
//        decltype(auto) operator++(int) {
//            return this->operator++();
//        }
//
//        bool operator==(const IteratorSentinel&) {
//            return !operator bool();
//        }
//
//        decltype(auto) begin() {
//            return *this;
//        }
//
//        decltype(auto) end() {
//            return IteratorSentinel{};
//        }
//    };
//
//    template <typename F>
//    struct filter {
//        F f;
//
//        constexpr filter(F&& f) : f(std::move(f)) {}
//
//        NonCopyableNonDefaultConstructible(filter);
//
//        using InputType = FunctionTypes::Sequence2;
//
//        constexpr auto operator()(auto generator) & = delete;
//
//        constexpr auto operator()(auto generator)&& {
//            return filter_iterator2(f, std::move(generator));
//        }
//    };
//
//    template <typename F>
//    concept Sequence = requires(F) {
//        { FunctionTypes::Sequence2{} } -> std::same_as<FunctionTypes::Sequence2>;
//    };
//
//    auto collect(Sequence auto&& seq) {
//        std::vector<std::remove_cvref_t<decltype(*seq.begin())>> res;
//        for (auto& e : seq)
//            res.push_back(e);
//        return res;
//    }
//
//    auto collect(auto&& e) {
//        Sequence auto s = filter_iterator2{e};
//        return e;
//    }
//
//    auto g(auto&& element, FunctionalOperation auto op) {
//        return std::move(op)(std::move(element));
//    }
//
//    auto op(auto&& operand, FunctionalOperation auto&&... operators) {
//        if constexpr (sizeof...(operators) == 0)
//            return operand;
//        else
//            return collect(g(std::move(operand), std::forward<decltype(operators)>(operators)...));
//    }
//}
