//#include <utility>
//#include <tuple>
//#include <vector>
//#include <list>
//
//#include "print.h"
//#include "int.h"
//
//#define Forward(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
//
//using namespace int_ns;
//using namespace named_values;
//
//template <typename E, typename F>
//struct result_type_of_op;
//
//struct InputTypes {
//    struct Sequence { using Seq = void; };
//    struct Element { using Elem = void; };
//};
//
//struct OutputTypes {
//    struct Element {};
//    struct OptionalElement {};
//};
//
//template <typename T>
//struct Sequence {
//    using value_type = T;
//};
//
//template <typename F>
//struct map {
//    F f;
//    using InputType = InputTypes::Sequence;
//};
//
//template <typename F>
//struct filter {
//    F f;
//    using InputType = InputTypes::Sequence;
//};
//
//template <typename F>
//struct until {
//    F f;
//    using InputType = InputTypes::Sequence;
//};
//
//template <typename F, typename InitialValue>
//struct fold {
//    F f;
//    InitialValue v;
//    using InputType = InputTypes::Sequence;
//};
//
//template <typename F>
//struct apply {
//    F f;
//    using InputType = InputTypes::Element;
//};
//
//template <template <typename...> typename Container>
//struct into {
//    using InputType = InputTypes::Sequence;
//};
//
//struct take {
//    int n;
//    using InputType = InputTypes::Sequence;
//};
//
//template <typename F>
//struct foreach {
//    F f;
//    using InputType = InputTypes::Sequence;
//};
//
////template <typename F, typename InitialValue, typename Until_f>
////struct fold_until {
////    F f;
////    InitialValue v;
////    until<Until_f> until;
////};
//
//template<std::size_t... indices>
//auto compute_fs_natural_order_tuple(auto&& arg, auto& refs_tuple, std::index_sequence<indices...>) {
//    return compute_fs_reverse_order(arg, Forward(std::get<sizeof...(indices) - indices - 1>(refs_tuple))...);
//}
//
//template<std::size_t... indices>
//auto compute_fs_natural_order_tuple(auto&& arg, auto&& refs_tuple, std::index_sequence<indices...>) {
//    return compute_fs_reverse_order(arg, std::move(std::get<sizeof...(indices) - indices - 1>(refs_tuple))...);
//}
//
//auto compute_fs_natural_order(auto&& arg, auto&&... fs) {
//    if constexpr (sizeof...(fs) == 0)
//        return arg;
//    else
//        return compute_fs_natural_order_tuple(
//            Forward(arg), std::forward_as_tuple(Forward(fs)...), std::make_index_sequence<sizeof...(fs)>{}
//    );
//}
//
//template <unsigned i = 0>
//auto compute_fs_natural_order_debug(auto&& arg, auto&&... fs) {
//    if constexpr (i == 0)
//        print_ns::print(arg);
//    if constexpr (sizeof...(fs) == 0) {
//        return arg;
//    }
//    else {
//        if constexpr (i + 1 < sizeof...(fs))
//            compute_fs_natural_order_debug<i + 1>(arg, fs...);
//        auto res = compute_fs_natural_order_tuple(
//            Forward(arg), std::forward_as_tuple(Forward(fs)...), std::make_index_sequence<sizeof...(fs) - i>{}
//        );
//        print_ns::print(res);
//        if constexpr ((sizeof...(fs)) == i + 1)
//            print_ns::print("\n");
//        return res;
//    }
//}
//
//auto compute_fs_reverse_order(auto&& val) {
//    return val;
//}
//
//auto prepare_vertical(auto&& val) {
//    return val;
//}
//
//auto prepare_vertical(auto&& val, auto&& next) {
//    using T = std::remove_cvref_t<decltype(next)>::InputType;
//    if constexpr (std::is_same_v<T, InputTypes::Sequence>)
//        return val;
//    else
//        return next.f(val);
//}
//
//auto prepare_vertical(auto&& val, auto&& next, auto&&... fs) {
//    using T = std::remove_cvref_t<decltype(next)>::InputType;
//    if constexpr (std::is_same_v<T, InputTypes::Sequence>) {
//        return prepare_vertical(Forward(val), Forward(fs)...);
//    }
//    else {
//        return next.f(compute_fs_reverse_order(Forward(val), Forward(fs)...));
//    }
//}
//
//bool vertically_apply(auto&& val, auto&& cb, auto&& f, auto&& next, auto&&... fs) {
//    using T = std::remove_cvref_t<decltype(next)>::InputType;
//    if constexpr (std::is_same_v<T, InputTypes::Sequence>)
//        return vertically_apply(Forward(val), [&cb, &f](auto&& e) {
//        vertically_apply(Forward(e), Forward(cb), Forward(f));
//            }, Forward(next), Forward(fs)...);
//    else
//        return vertically_apply(Forward(val), Forward(cb), Forward(f));
//}
//
//template <typename F>
//bool vertically_apply(auto&& val, auto&& cb, apply<F>&& f, auto&&... fs) {
//    cb(val);
//    return true;
//}
//
//template <typename F>
//bool vertically_apply(auto&& val, auto&& cb, take&& t, auto&&... fs) {
//    if (t.n == 0)
//        return false;
//    cb(val);
//    t.n -= 1;
//    return true;
//}
//
//template <typename F>
//auto compute_fs_reverse_order(auto&& val, apply<F>&& f) {
//    return f.f(val);
//}
//
//template <typename F>
//auto compute_fs_reverse_order(auto&& val, apply<F>&& f, auto&&... fs) {
//    return f.f(compute_fs_reverse_order(val, Forward(fs)...));
//}
//
//template <typename F>
//auto compute_fs_reverse_order(auto&& val, map<F>&& f, auto&&... fs) {
//    return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//}
//
//template <typename F>
//auto compute_fs_reverse_order(auto&& val, filter<F>&& f, auto&&... fs) {
//    return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//}
//
//template <typename F>
//auto compute_fs_reverse_order(auto&& val, until<F>&& f, auto&&... fs) {
//    return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//}
//
//auto compute_fs_reverse_order(auto&& val, take&& f, auto&&... fs) {
//    return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//}
//
//template <typename F, typename V>
//auto compute_fs_reverse_order(auto&& val, fold<F, V>&& f) {
//    auto res = f.v;
//    for (auto& e : val)
//        res = f.f(res, e);
//    return res;
//}
//
//template <typename F, typename V>
//auto compute_fs_reverse_order(auto&& val, fold<F, V>&& f, auto&&... fs) {
//    auto res = f.v;
//    auto arg_to_apply_vertically_on = prepare_vertical(Forward(val), fs...);
//    for (auto& e : arg_to_apply_vertically_on)
//        if (!vertically_apply(e, [&res, &f](auto&& e) { res = f.f(res, e); }, Forward(fs)...))
//            break;
//    return res;
//}
//
//auto compute_fs_reverse_order(auto&& val, into<std::vector>&&) {
//    std::vector<std::remove_cvref_t<decltype(val)>::value_type> res;
//    res.reserve(val.size());
//    for (auto& e : val)
//        res.push_back(e);
//    return res;
//}
//
//auto compute_fs_reverse_order(auto&& val, into<std::vector>&&, auto&&... fs) {
//    std::vector<int> res;
//    auto arg_to_apply_vertically_on = prepare_vertical(Forward(val), fs...);
//    for (auto& e : arg_to_apply_vertically_on)
//        if (!vertically_apply(e, [&res](auto&& e) { res.push_back(e); }, Forward(fs)...))
//            break;
//    return res;
//}
//
//bool vertically_apply(auto&& val, auto&& cb) {
//    cb(val);
//    return true;
//}
//
//template <typename F>
//bool vertically_apply(auto&& val, auto&& cb, map<F>&& f) {
//    cb(f.f(val));
//    return true;
//}
//
//bool vertically_apply(auto&& val, auto&& cb, take&& f) {
//    if (f.n == 0)
//        return false;
//    cb(val);
//    f.n -= 1;
//    return true;
//}
//
//template <typename F>
//bool vertically_apply(auto&& val, auto&& cb, filter<F>&& f) {
//    if (f.f(val))
//        cb(val);
//    return true;
//}
//
//template <typename F>
//bool vertically_apply(auto&& val, auto&& cb, until<F>&& f) {
//    if (f.f(val))
//        return false;
//    cb(val);
//    return true;
//}
//
//int main() {
//    auto iota = [](unsigned n) {
//        std::vector<unsigned> res(n, 0);
//        for (unsigned i = 0; i < n; ++i)
//            res[i] = i + 1;
//        return res;
//    };
//
//    auto v1 = iota(10);
//
//    auto square = [](unsigned x) {
//        return x * x;
//    };
//
//    auto even = [](unsigned x) {
//        return x % 2 == 0;
//    };
//
//    auto sum = [](auto&& cur, auto&& next) {
//        return cur + next;
//    };
//
//    auto sum_of_squares = [&](unsigned i) {
//        return compute_fs_natural_order(
//            i
//            , apply{ iota }
//            , map{ square }
//            , fold{ sum, 0 }
//        );
//    };
//    print_ns::println(sum_of_squares(7));
//
//    print_ns::println(
//        compute_fs_natural_order(
//            v1
//            , map{ square }
//            , filter{ even }
//            , map{ square }
//        )
//    );
//    print_ns::println(
//        compute_fs_natural_order(
//            v1
//            , filter{ even }
//        ),
//        compute_fs_natural_order(
//            v1
//            , filter{ even }
//            , fold{ sum, 0 }
//        ),
//        compute_fs_natural_order(
//            v1
//            , filter{ even }
//            , fold{ sum, 0 }
//            , apply{ square }
//        )
//    );
//    compute_fs_natural_order_debug(
//        5
//        , apply{ iota }
//        , filter{ even }
//        , fold{ sum, 0 }
//        , apply{ iota }
//    );
//    compute_fs_natural_order_debug(
//        20
//        , apply{ iota }
//    , until{ [](auto x) { return x > 5; } }
//        , take{ 5 }
//        , fold{ sum, 0 }
//    );
//    compute_fs_natural_order_debug(
//        iota(7),
//        take(1)
//    );
//
//    return 0;
//
//    /*print_ns::println(v1);
//    print_ns::println(
//        compute(
//            v1
//            , map    { [](auto i) { return i + 1; } }
//            , filter { [](auto i) { return i % 2; } }
//            , until  { [](auto i) { return i > 5; } }
//        ),
//        compute(
//            v1
//            , map{ [](auto i) { return i + 1; } }
//            , in<std::list>{}
//        )
//    );
//
//    auto sum = fold{ [](auto& cur, auto& next) { return cur + next; }, 0 };
//    print_ns::println(
//        compute(
//            v1
//            , map    { [](auto i) { return i + 1; } }
//            , filter { [](auto i) { return i % 2; } }
//            , until  { [](auto i) { return i > 5; } }
//            , sum
//        ),
//        compute(
//            v1
//            , sum
//        )
//    );
//
//    return 0;*/
//
//    /*
//    map f, map g:
//        res = T[]
//        for e in seq:
//            res += [g(f(e))]
//        return res;
//
//    map f, apply g:
//        res = T[]
//        for e in seq:
//            res += [f(e)]
//        return g(res);
//
//    map f, fold g, apply h:
//        res = g.val;
//        for e in seq:
//            res = g(res, f(e))
//        return h(res);
//
//    map f, fold g, apply h, map i, apply j, fold k:
//        res = g.val
//
//        for e in seq:
//            res = g(res, e)
//
//        res' = T[]
//        for e in h(res):
//            res' += [i(e)]
//
//        res'' = j(res')
//
//        res''' = k.val;
//        for e in res':
//            res''' = k(res''', e)
//        return res''';
//    */
//
//    return 0;
//}
//
//
//
//
//
//
////#include "generic_functions.h"
////#include "iterators.h"
////#include "iterators2.h"
////#include <chrono>
////
////int main() {
////
////    using namespace print_ns;
////
////    auto iters = 100000;
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto sum = [](const auto& vec) { return 0; };
////            auto v1 = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            auto temp = iterators2::op(
////                iterators2::structure_iterator{ v1.begin(), v1.end() }
////                , iterators2::filter{ [](const auto& e) { return e % 2 != 0; } }
////            );
////        }
////        std::cout << "functional clean iterators2: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto sumFirst5 = partial_fold{ [count = 0] (auto x, auto y) mutable {
////                if (count++ == 5)
////                    return std::optional<std::remove_reference_t<decltype(x + y)>>{};
////                else
////                    return std::optional{ x + y };
////            }, 0 };
////
////            auto temp = op(
////                std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
////                std::move(sumFirst5)
////            );
////        }
////        std::cout << "functional unclean coroutines: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto temp = op(
////                std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
////                take(5),
////                futil::folds::sum()
////            );
////        }
////        std::cout << "functional clean coroutines: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////
////            auto sum = [](const auto& vec) { return 0; };
////            auto v1 = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            auto temp = iterators::op(
////                v1,
////                iterators::take{ 5 }
////            );
////        }
////        std::cout << "functional clean iterators: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            auto sum = [](auto&& v) {
////                auto res = std::remove_cvref_t<decltype(v.at(0))>{};
////                for (auto& e : v)
////                    res += e;
////                return res;
////            };
////            auto first5 = [](auto& v) {
////                return std::remove_cvref_t<decltype(v)> {v.begin(), v.begin() + (v.size() >= 5 ? 5 : v.size())};
////            };
////            auto temp = sum(first5(v));
////        }
////        std::cout << "function taking vec decomposed: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            auto sumFirst5 = [](auto& v) {
////                auto res = v.at(0) - v.at(0);
////                for (int j = 0; j < 5; ++j)
////                    res += v.at(j);
////                return res;
////            };
////            auto temp = sumFirst5(v);
////        }
////        std::cout << "function taking vec: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            int sumOfFirstFive = 0;
////            for (int j = 0; j < 5; ++j)
////                sumOfFirstFive += v.at(j);
////        }
////        std::cout << "raw loop: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    {
////        auto t1 = std::chrono::high_resolution_clock::now();
////        for (int i = 0; i < iters; ++i) {
////            auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////            auto sumOfFirstFive = v.at(0) + v.at(1) + v.at(2) + v.at(3) + v.at(4);
////        }
////        std::cout << "raw sum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
////    }
////    return 0;
////
////    //using print_ns::println;
////
////    //std::vector<int> v1 = { 1, 2, 3 };
////
////    //{
////    //    auto temp = op(std::stringstream{"123"});
////    //    println(temp);
////    //}
////
////    //{
////    //    auto temp = op(v1, // 1, 2, 3
////    //        map{ [](auto x) { return -x; } }); // -1,-2,-3
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1, // 1,2,3
////    //        map{ [](auto x) { return -x; } },  // -1,-2,-3
////    //        map{ [](auto x) { return 2 * x; } },  // -2,-4,-6
////    //        map{ [](auto x) { return std::to_string(x); } }); // "-2", "-4", "-6"
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
////    //        map{ [](auto x) { return 2 * x; } }); // 2, 6
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
////    //        map{ [](auto x) { return 2 * x; } }, // 2, 6
////    //        fold{ [](auto x, auto y) { return x + y; }, 0 }); // 8
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(5,
////    //        apply{ [](auto x) { return x; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(5,
////    //        apply{ [](auto x) { return x + 1; } }, // 6
////    //        apply{ [](auto x) {
////    //            std::vector<double> res(x);
////    //            for (int i = 1; i < x; ++i)
////    //                res[i] = 1.0 / i;
////    //            return res;
////    //        } }                                    // [0, 1, 0.5, 0.333, 0.25, 0.2]
////    //    );
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
////    //        map{ [](auto x) { return 2 * x; } }, // 2, 6
////    //        fold{ [](auto x, auto y) { return x + y; }, 0 }, // 8
////    //        apply{ [](auto x) { return std::to_string(x); } }); // "8"
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        apply{ [](auto x) { return x; } }); // apply: x is the vector
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        apply{ [](auto x) { return x; } },
////    //        apply{ [](auto x) { return x; } },
////    //        apply{ [](auto x) { return x; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        apply{ [](auto x) { return x; } }, // apply: x is the vector
////    //        map{ [](auto x) { return x + 1; } }); // map: x is an element
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(5,
////    //        apply{ [](auto x) { return x + 1; } }, // 6
////    //        apply{ [](auto x) {
////    //            std::vector<double> res(x);
////    //            for (int i = 1; i < x; ++i)
////    //                res[i] = 1.0 / i;
////    //            return res;
////    //        } },                                   // [0, 1, 0.5, 0.333, 0.25, 0.2]
////    //        map{ [](auto x) { return 1 - x; } }
////    //    );
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x; } },
////    //        apply{ [](auto x) { return x; } },
////    //        filter{ [](auto x) { return x % 2; } },
////    //        apply{ [](auto x) { return x; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x; } },
////    //        apply{ [](auto x) { return x; } },
////    //        filter{ [](auto x) { return x % 2; } },
////    //        find{ [&](auto x) { return x == 3; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto sumFirst5 = []() {
////    //        return partial_fold{ [count=0](auto x, auto y) mutable {
////    //            if (count++ == 5)
////    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{};
////    //            else
////    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
////    //        }, 0 }; };
////
////    //    auto temp = op(
////    //        std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
////    //        sumFirst5()
////    //    );
////    //    println(temp);
////    //}
////    //{
////    //    auto sumUntilNexcluded = [](int n) {
////    //        return partial_fold{ [n](auto x, auto y) {
////    //            if (y == n)
////    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{};
////    //            else
////    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
////    //        }, 0 };
////    //    };
////
////    //    auto temp = op(
////    //        std::vector<int>{1, 3, 5, 7},
////    //        sumUntilNexcluded(7)
////    //    );
////    //    println(temp);
////    //}
////    //{
////    //    // take(n) "takes" first n elements
////    //    auto take = [](int n) {
////    //        int count = 0;
////    //        return partial_filter{ [&count, n](auto x) {
////    //            if (count++ == n)
////    //                return std::optional<bool>{ std::nullopt };
////    //            else
////    //                return std::optional<bool>{ true };
////    //        } };
////    //    };
////    //    auto temp = op(
////    //        std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
////    //        take(5)
////    //    );
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x; } },
////    //        apply{ [](auto x) { return x; } },
////    //        filter{ [](auto x) { return x % 2; } },
////    //        foreach{ futil::operations::println() },
////    //        find{ [](auto x) { return x > 1; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x; } });
////    //    println(temp);
////    //}
////    //{
////    //    auto weird_format = []() { return complex_fold{
////    //            [](auto default_value, auto first) { default_value << first; return default_value; },
////    //            [](auto current_value, auto next) { current_value << " : " << next; return current_value; },
////    //            [](auto current_value) { current_value << "}"; return current_value.str(); },
////    //            []() { std::stringstream ss; ss << "{"; return ss; }()
////    //    }; };
////    //    {
////    //        auto temp = op(v1,// 1,2,3
////    //            futil::conversions::maps::to_string(),
////    //            futil::conversions::maps::to_string(),
////    //            futil::conversions::maps::to_string(),// "1", "2", "3"
////    //            weird_format()); // {1 : 2 : 3}
////    //        println(temp);
////    //    }
////    //    {
////    //        auto temp = op(std::vector<int>{},
////    //            futil::conversions::maps::to_string(),
////    //            weird_format()); // {}
////    //        println(temp);
////    //    }
////    //}
////    //{
////    //    auto weird_format = complex_fold{
////    //            [](auto default_value, auto first) { default_value << first; return default_value; },
////    //            [](auto current_value, auto next) { current_value << " : " << next; return current_value; },
////    //            [](auto current_value) { current_value << "}"; return current_value.str(); },
////    //            []() { std::stringstream ss; ss << "{"; return ss; }()
////    //    };
////    //    {
////    //        auto temp = op(v1,// 1,2,3
////    //            futil::conversions::maps::to_string(),
////    //            futil::conversions::maps::to_string(),
////    //            futil::conversions::maps::to_string(),// "1", "2", "3"
////    //            std::move(weird_format)); // {1 : 2 : 3}
////    //        println(temp);
////    //    }
////    //}
////    //{
////    //    int k = 3;
////    //    auto f1 = map{ [&](auto x) { return x * k++; } };
////    //    auto f2 = futil::manipulations::maps::index_from(1);
////    //    auto f3 = futil::collectors::tomap<int, int>();
////    //    {
////    //        auto temp = op(v1, // 1,2,3
////    //            std::move(f1), // 1*3, 2*4, 3*5
////    //            std::move(f2),
////    //            std::move(f3));
////    //        println(temp); // [{ 1, 3 }, { 2, 8 }, { 3, 15 }]
////    //    }
////    //    {
////    //        auto temp = op(v1, // 1,2,3
////    //            std::move(f1), // 1*6, 2*7, 3*8
////    //            std::move(f2),
////    //            std::move(f3));
////    //        println(temp); // [{ 1, 6 }, { 2, 14 }, { 3, 24 }]
////    //    }
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x * x; } }, // 1,4,9
////    //        futil::manipulations::maps::index_from_zero(), // {0, 1}, {1, 4}, {2, 9}
////    //        futil::manipulations::maps::index_from_zero()); // {0, {0, 1}}, {1, {1, 4}}, {2, {2, 9}}
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x * x; } }, // 1,4,9
////    //        futil::manipulations::maps::index_from(1));
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x * x; } }, // 1,4,9
////    //        futil::manipulations::maps::reverse_index_from(1));
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        futil::folds::sum());
////    //    println(temp);
////    //}
////    //{
////    //    auto temp = op(v1,// 1,2,3
////    //        map{ [](auto x) { return x * x; } }, // 1,4,9
////    //        futil::manipulations::maps::index_from(1),
////    //        futil::collectors::tomap<int, int>());
////    //    println(temp);
////    //}
////
////    return 0;
////}
