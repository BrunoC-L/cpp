#include <utility>
#include <tuple>
#include <vector>
#include <list>
#include <optional>
#include <chrono>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <thread>

#include "generated.h"
#include "print.h"
using namespace std::chrono_literals;
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

int main() {
    using namespace print_ns;
    auto iters = 1000*1000;
    const auto v1 = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto iota = [](unsigned n) {
        std::vector<unsigned> res(n, 0);
        for (unsigned i = 0; i < n; ++i)
            res[i] = i;
        return res;
    };
    /*{
        int ttl = 0;
        std::this_thread::sleep_for(50ms);
        auto v = iota(100);
        auto even = generated::filter{ [](const auto& e) { return e % 2 == 0; } };
        auto square = generated::map{ [](const auto& e) { return e * e; } };
        auto sum = generated::fold{ [](auto&& cur, auto&& next) {
            return cur + next;
        }, 0 };
        auto take_under_600 = generated::take_while{ [](const auto& e) { return e < 600; } };
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i)
            ttl += generated::compute(
                v
                , even
                , generated::take{ 25 }
                , square
                , take_under_600
                , sum
            );
        std::cout << ttl << "\n";
        std::cout << "functional clean generated longer test: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    //{
    //    //std::this_thread::sleep_for(500ms);
    //    int ttl = 0;
    //    auto sum = generated::fold{ [](auto&& cur, auto&& next) {
    //        return cur + next;
    //    }, 0 };
    //    auto t1 = std::chrono::high_resolution_clock::now();
    //    for (int i = 0; i < iters; ++i)
    //        ttl += generated::compute(
    //            v1
    //            , generated::take{ 5 }
    //            , sum
    //        );
    //    std::cout << ttl << "\n";
    //    std::cout << "functional clean generated: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    //}
    {
        //std::this_thread::sleep_for(500ms);
        int ttl = 0;
        auto sum = generated::fold{ [](auto&& cur, auto&& next) {
            return cur + next;
        }, 0 };
        auto t1 = std::chrono::high_resolution_clock::now();
        double d;
        ankerl::nanobench::Bench().run("some double ops", [&] {
            for (int i = 0; i < iters; ++i)
                d += generated::compute(
                    v1
                    , generated::take{ 5 }
                    , sum
                );
            ankerl::nanobench::doNotOptimizeAway(d);
        });
    }
    /*{
        auto t1 = std::chrono::high_resolution_clock::now();
        auto tk = inline_fs::take{ 5 };
        auto sum = inline_fs::fold{ [](auto&& cur, auto&& next) {
            return cur + next;
        }, 0 };
        for (int i = 0; i < iters; ++i)
            auto temp = compute_fs_natural_order(
                v1
                , tk
                , sum
            );
        std::cout << "functional clean: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    /*{
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i) {
            auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            auto sum = [](auto&& v) {
                using T = std::decay<decltype(v.at(0))>::type;
                auto res = T{};
                for (auto& e : v)
                    res += e;
                return res;
            };
            auto first5 = [](auto& v) {
                using T = std::decay<decltype(v)>::type;
                return T{v.begin(), v.begin() + (v.size() >= 5 ? 5 : v.size())};
            };
            auto temp = sum(first5(v));
        }
        std::cout << "function taking vec decomposed: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    /*{
        auto sumFirst5 = [](auto& v) {
            int sumOfFirstFive = 0;
            int t = 5;
            for (auto& e : v) {
                if (t == 0)
                    break;
                t -= 1;
                sumOfFirstFive += e;
            }
            return sumOfFirstFive;
        };
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i)
            auto temp = sumFirst5(v1);
        std::cout << "function taking vec: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    {
        auto sumFirst5 = [](auto& v) {
            int sumOfFirstFive = 0;
            int t = 5;
            for (auto& e : v) {
                if (t == 0)
                    break;
                t -= 1;
                sumOfFirstFive += e;
            }
            return sumOfFirstFive;
        };
        double d;
        ankerl::nanobench::Bench().run("some double ops2", [&] {
            for (int i = 0; i < iters; ++i)
                d += sumFirst5(v1);
            ankerl::nanobench::doNotOptimizeAway(d);
        });
    }
    /*{
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i) {
            int sumOfFirstFive = 0;
            int t = 5;
            for (auto& e : v1) {
                if (t == 0)
                    break;
                t -= 1;
                sumOfFirstFive += e;
            }
        }
        std::cout << "augmented loop sum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i) {
            int sumOfFirstFive = 0;
            for (int j = 0; j < 5; ++j)
                sumOfFirstFive += v1.at(j);
        }
        std::cout << "loop sum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i)
            auto sumOfFirstFive = v1.at(0) + v1.at(1) + v1.at(2) + v1.at(3) + v1.at(4);
        std::cout << "index sum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i) {
            const int* data = v1.data();
            auto sumOfFirstFive = data[0] + data[1] + data[2] + data[3] + data[4];
        }
        std::cout << "bypass sum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        const int* data = v1.data();
        for (int i = 0; i < iters; ++i)
            auto sumOfFirstFive = data[0] + data[1] + data[2] + data[3] + data[4];
        std::cout << "bypass sum known ptr: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        std::this_thread::sleep_for(50ms);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i)
            auto sumOfFirstFive = 1 + 2 + 3 + 4 + 5;
        std::cout << "absolute minimum: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    /*{
        auto t1 = std::chrono::high_resolution_clock::now();
        auto sumFirst5 = partial_fold{ [count = 0] (auto x, auto y) mutable {
            if (count++ == 5)
                return std::optional<std::remove_reference_t<decltype(x + y)>>{};
            else
                return std::optional{ x + y };
        }, 0 };
        for (int i = 0; i < iters; ++i) {
            auto temp = op(
                v1,
                std::move(sumFirst5)
            );
        }
        std::cout << "functional unclean coroutines: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iters; ++i) {
            auto temp = op(
                v1,
                take(5),
                futil::folds::sum()
            );
        }
        std::cout << "functional clean coroutines: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    return 0;
    /*auto iota = [](unsigned n) {
        std::vector<unsigned> res(n, 0);
        for (unsigned i = 0; i < n; ++i)
            res[i] = i + 1;
        return res;
    };

    auto v1 = iota(10);

    auto square = [](auto x) {
        return x * x;
    };

    auto even = [](unsigned x) {
        return x % 2 == 0;
    };

    auto sum = [](auto&& cur, auto&& next) {
        return cur + next;
    };

    print_ns::println(
        compute_fs_natural_order(
            v1
            , inline_fs::map{ square }
        )
    );

    print_ns::println(
        compute_fs_natural_order(
            v1
            , inline_fs::map{ square }
            , inline_fs::filter{ even }
        )
    );

    print_ns::println(
        compute_fs_natural_order(
            v1
            , inline_fs::map{ square }
            , inline_fs::filter{ even }
            , inline_fs::map{ square }
        )
    );

    auto sum_of_squares = [&](unsigned i) {
        return compute_fs_natural_order(
            i
            , inline_fs::apply{ iota }
            , inline_fs::map{ square }
            , inline_fs::fold{ sum, 0 }
        );
    };
    print_ns::println(sum_of_squares(7));

    print_ns::println(
        compute_fs_natural_order(
            v1
            , inline_fs::filter{ even }
        ),
        compute_fs_natural_order(
            v1
            , inline_fs::filter{ even }
            , inline_fs::fold{ sum, 0 }
        ),
        compute_fs_natural_order(
            v1
            , inline_fs::filter{ even }
            , inline_fs::fold{ sum, 0 }
            , inline_fs::apply{ square }
        )
    );
    compute_fs_natural_order_debug(
        5
        , inline_fs::apply{ iota }
        , inline_fs::filter{ even }
        , inline_fs::fold{ sum, 0 }
        , inline_fs::apply{ iota }
    );
    compute_fs_natural_order_debug(
        20
        , inline_fs::apply{ iota }
        , inline_fs::until { [](auto x) { return x > 5;} }
        , inline_fs::take{ 5 }
        , inline_fs::fold{ sum, 0 }
    );
    compute_fs_natural_order_debug(
        iota(7),
        inline_fs::take(1)
    );*/
    /*{
        auto t1 = std::chrono::high_resolution_clock::now();
        auto tk = inline_fs::take(5);
        auto sum = inline_fs::fold{ [](auto&& cur, auto&& next) {
            return cur + next;
        }, 0 };
        for (int i = 0; i < iters; ++i) {
            auto temp = compute_fs_natural_order(
                v1
                , tk
                , sum
            );
        }
        std::cout << "functional clean inline: " << (std::chrono::high_resolution_clock::now() - t1).count() / 1000000.0 << "ms\n";
    }*/
    return 0;
    //using print_ns::println;

    //std::vector<int> v1 = { 1, 2, 3 };

    //{
    //    auto temp = op(std::stringstream{"123"});
    //    println(temp);
    //}

    //{
    //    auto temp = op(v1, // 1, 2, 3
    //        map{ [](auto x) { return -x; } }); // -1,-2,-3
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1, // 1,2,3
    //        map{ [](auto x) { return -x; } },  // -1,-2,-3
    //        map{ [](auto x) { return 2 * x; } },  // -2,-4,-6
    //        map{ [](auto x) { return std::to_string(x); } }); // "-2", "-4", "-6"
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
    //        map{ [](auto x) { return 2 * x; } }); // 2, 6
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
    //        map{ [](auto x) { return 2 * x; } }, // 2, 6
    //        fold{ [](auto x, auto y) { return x + y; }, 0 }); // 8
    //    println(temp);
    //}
    //{
    //    auto temp = op(5,
    //        apply{ [](auto x) { return x; } });
    //    println(temp);
    //}
    //{
    //    auto temp = op(5,
    //        apply{ [](auto x) { return x + 1; } }, // 6
    //        apply{ [](auto x) {
    //            std::vector<double> res(x);
    //            for (int i = 1; i < x; ++i)
    //                res[i] = 1.0 / i;
    //            return res;
    //        } }                                    // [0, 1, 0.5, 0.333, 0.25, 0.2]
    //    );
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        filter{ [](auto x) { return x % 2; } }, // 1, 3
    //        map{ [](auto x) { return 2 * x; } }, // 2, 6
    //        fold{ [](auto x, auto y) { return x + y; }, 0 }, // 8
    //        apply{ [](auto x) { return std::to_string(x); } }); // "8"
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        apply{ [](auto x) { return x; } }); // apply: x is the vector
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        apply{ [](auto x) { return x; } },
    //        apply{ [](auto x) { return x; } },
    //        apply{ [](auto x) { return x; } });
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        apply{ [](auto x) { return x; } }, // apply: x is the vector
    //        map{ [](auto x) { return x + 1; } }); // map: x is an element
    //    println(temp);
    //}
    //{
    //    auto temp = op(5,
    //        apply{ [](auto x) { return x + 1; } }, // 6
    //        apply{ [](auto x) {
    //            std::vector<double> res(x);
    //            for (int i = 1; i < x; ++i)
    //                res[i] = 1.0 / i;
    //            return res;
    //        } },                                   // [0, 1, 0.5, 0.333, 0.25, 0.2]
    //        map{ [](auto x) { return 1 - x; } }
    //    );
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x; } },
    //        apply{ [](auto x) { return x; } },
    //        filter{ [](auto x) { return x % 2; } },
    //        apply{ [](auto x) { return x; } });
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x; } },
    //        apply{ [](auto x) { return x; } },
    //        filter{ [](auto x) { return x % 2; } },
    //        find{ [&](auto x) { return x == 3; } });
    //    println(temp);
    //}
    //{
    //    auto sumFirst5 = []() {
    //        return partial_fold{ [count=0](auto x, auto y) mutable {
    //            if (count++ == 5)
    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{};
    //            else
    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
    //        }, 0 }; };

    //    auto temp = op(
    //        std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    //        sumFirst5()
    //    );
    //    println(temp);
    //}
    //{
    //    auto sumUntilNexcluded = [](int n) {
    //        return partial_fold{ [n](auto x, auto y) {
    //            if (y == n)
    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{};
    //            else
    //                return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
    //        }, 0 };
    //    };

    //    auto temp = op(
    //        std::vector<int>{1, 3, 5, 7},
    //        sumUntilNexcluded(7)
    //    );
    //    println(temp);
    //}
    //{
    //    // take(n) "takes" first n elements
    //    auto take = [](int n) {
    //        int count = 0;
    //        return partial_filter{ [&count, n](auto x) {
    //            if (count++ == n)
    //                return std::optional<bool>{ std::nullopt };
    //            else
    //                return std::optional<bool>{ true };
    //        } };
    //    };
    //    auto temp = op(
    //        std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    //        take(5)
    //    );
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x; } },
    //        apply{ [](auto x) { return x; } },
    //        filter{ [](auto x) { return x % 2; } },
    //        foreach{ futil::operations::println() },
    //        find{ [](auto x) { return x > 1; } });
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x; } });
    //    println(temp);
    //}
    //{
    //    auto weird_format = []() { return complex_fold{
    //            [](auto default_value, auto first) { default_value << first; return default_value; },
    //            [](auto current_value, auto next) { current_value << " : " << next; return current_value; },
    //            [](auto current_value) { current_value << "}"; return current_value.str(); },
    //            []() { std::stringstream ss; ss << "{"; return ss; }()
    //    }; };
    //    {
    //        auto temp = op(v1,// 1,2,3
    //            futil::conversions::maps::to_string(),
    //            futil::conversions::maps::to_string(),
    //            futil::conversions::maps::to_string(),// "1", "2", "3"
    //            weird_format()); // {1 : 2 : 3}
    //        println(temp);
    //    }
    //    {
    //        auto temp = op(std::vector<int>{},
    //            futil::conversions::maps::to_string(),
    //            weird_format()); // {}
    //        println(temp);
    //    }
    //}
    //{
    //    auto weird_format = complex_fold{
    //            [](auto default_value, auto first) { default_value << first; return default_value; },
    //            [](auto current_value, auto next) { current_value << " : " << next; return current_value; },
    //            [](auto current_value) { current_value << "}"; return current_value.str(); },
    //            []() { std::stringstream ss; ss << "{"; return ss; }()
    //    };
    //    {
    //        auto temp = op(v1,// 1,2,3
    //            futil::conversions::maps::to_string(),
    //            futil::conversions::maps::to_string(),
    //            futil::conversions::maps::to_string(),// "1", "2", "3"
    //            std::move(weird_format)); // {1 : 2 : 3}
    //        println(temp);
    //    }
    //}
    //{
    //    int k = 3;
    //    auto f1 = map{ [&](auto x) { return x * k++; } };
    //    auto f2 = futil::manipulations::maps::index_from(1);
    //    auto f3 = futil::collectors::tomap<int, int>();
    //    {
    //        auto temp = op(v1, // 1,2,3
    //            std::move(f1), // 1*3, 2*4, 3*5
    //            std::move(f2),
    //            std::move(f3));
    //        println(temp); // [{ 1, 3 }, { 2, 8 }, { 3, 15 }]
    //    }
    //    {
    //        auto temp = op(v1, // 1,2,3
    //            std::move(f1), // 1*6, 2*7, 3*8
    //            std::move(f2),
    //            std::move(f3));
    //        println(temp); // [{ 1, 6 }, { 2, 14 }, { 3, 24 }]
    //    }
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x * x; } }, // 1,4,9
    //        futil::manipulations::maps::index_from_zero(), // {0, 1}, {1, 4}, {2, 9}
    //        futil::manipulations::maps::index_from_zero()); // {0, {0, 1}}, {1, {1, 4}}, {2, {2, 9}}
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x * x; } }, // 1,4,9
    //        futil::manipulations::maps::index_from(1));
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x * x; } }, // 1,4,9
    //        futil::manipulations::maps::reverse_index_from(1));
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        futil::folds::sum());
    //    println(temp);
    //}
    //{
    //    auto temp = op(v1,// 1,2,3
    //        map{ [](auto x) { return x * x; } }, // 1,4,9
    //        futil::manipulations::maps::index_from(1),
    //        futil::collectors::tomap<int, int>());
    //    println(temp);
    //}

    return 0;
}

//
//namespace inline_fs {
//
//#define Forward(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
//
//    using namespace int_ns;
//    using namespace named_values;
//
//    struct InputTypes {
//        struct Sequence { using Seq = void; };
//        struct Element { using Elem = void; };
//    };
//
//    template <typename F>
//    struct map {
//        F f;
//        using InputType = InputTypes::Sequence;
//    };
//
//    template <typename F>
//    struct filter {
//        F f;
//        using InputType = InputTypes::Sequence;
//    };
//
//    template <typename F>
//    struct until {
//        F f;
//        using InputType = InputTypes::Sequence;
//    };
//
//    template <typename F, typename InitialValue>
//    struct fold {
//        F f;
//        InitialValue v;
//        using InputType = InputTypes::Sequence;
//    };
//
//    template <typename F>
//    struct apply {
//        F f;
//        using InputType = InputTypes::Element;
//    };
//
//    template <template <typename...> typename Container>
//    struct into {
//        using InputType = InputTypes::Sequence;
//    };
//
//    struct take {
//        int n;
//        using InputType = InputTypes::Sequence;
//    };
//
//    template<std::size_t... indices>
//    auto compute_fs_natural_order_tuple(auto&& arg, auto& refs_tuple, std::index_sequence<indices...>) {
//        return compute_fs_reverse_order(arg, Forward(std::get<sizeof...(indices) - indices - 1>(refs_tuple))...);
//    }
//
//    template<std::size_t... indices>
//    auto compute_fs_natural_order_tuple(auto&& arg, auto&& refs_tuple, std::index_sequence<indices...>) {
//        return compute_fs_reverse_order(arg, std::move(std::get<sizeof...(indices) - indices - 1>(refs_tuple))...);
//    }
//
//    auto compute_fs_natural_order(auto&& arg, auto&&... fs) {
//        if constexpr (sizeof...(fs) == 0)
//            return arg;
//        else
//            return compute_fs_natural_order_tuple(
//                Forward(arg), std::forward_as_tuple(Forward(fs)...), std::make_index_sequence<sizeof...(fs)>{}
//        );
//    }
//
//    template <unsigned i = 0>
//    auto compute_fs_natural_order_debug(auto&& arg, auto&&... fs) {
//        if constexpr (i == 0) {
//            print_ns::println();
//            print_ns::print(arg);
//        }
//        if constexpr (sizeof...(fs) == 0) {
//            return arg;
//        }
//        else {
//            if constexpr (i + 1 < sizeof...(fs))
//                compute_fs_natural_order_debug<i + 1>(arg, fs...);
//            auto res = compute_fs_natural_order_tuple(
//                Forward(arg), std::forward_as_tuple(Forward(fs)...), std::make_index_sequence<sizeof...(fs) - i>{}
//            );
//            print_ns::print(res);
//            if constexpr ((sizeof...(fs)) == i + 1)
//                print_ns::println();
//            return res;
//        }
//    }
//
//    auto compute_fs_reverse_order(auto&& val) {
//        return val;
//    }
//
//    auto prepare_vertical(auto&& val) {
//        return val;
//    }
//
//    auto prepare_vertical(auto&& val, auto&& next) {
//        using T = decltype(next)::InputType;
//        if constexpr (std::is_same_v<T, InputTypes::Sequence>)
//            return val;
//        else
//            return next.f(val);
//    }
//
//    auto prepare_vertical(auto&& val, auto&& next, auto&&... fs) {
//        using T = typename decltype(next)::InputType;
//        if constexpr (std::is_same_v<T, InputTypes::Sequence>) {
//            return prepare_vertical(Forward(val), Forward(fs)...);
//        }
//        else {
//            return next.f(compute_fs_reverse_order(Forward(val), Forward(fs)...));
//        }
//    }
//
//    auto vertically_apply(auto&& val, auto&& f, auto&& next, auto&&... fs) {
//        using T = typename decltype(next)::InputType;
//        if constexpr (std::is_same_v<T, InputTypes::Sequence>) {
//            auto [e, kg] = vertically_apply(Forward(val), Forward(next), Forward(fs)...);
//            if (e.has_value() && kg)
//                return vertically_apply(std::move(e.value()), Forward(f));
//            else
//                return decltype(vertically_apply(std::move(e.value()), Forward(f))){ {}, kg};
//        }
//        else
//            return vertically_apply(Forward(val), Forward(f));
//    }
//
//    template <typename F>
//    auto vertically_apply(auto&& val, apply<F>&& f, auto&&... fs) {
//        return std::pair{ std::optional { val }, true };
//    }
//
//    template <typename F>
//    auto vertically_apply(auto&& val, take&& t, auto&&... fs) {
//        if (t.n == 0)
//            return std::pair{ decltype(std::optional { val }) { }, false };
//        else {
//            t.n -= 1;
//            return std::pair{ std::optional { val }, true };
//        }
//    }
//
//    template <typename F>
//    auto compute_fs_reverse_order(auto&& val, apply<F>&& f) {
//        return f.f(val);
//    }
//
//    template <typename F>
//    auto compute_fs_reverse_order(auto&& val, apply<F>&& f, auto&&... fs) {
//        return f.f(compute_fs_reverse_order(val, Forward(fs)...));
//    }
//
//    template <typename F>
//    auto compute_fs_reverse_order(auto&& val, map<F>&& f, auto&&... fs) {
//        return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//    }
//
//    template <typename F>
//    auto compute_fs_reverse_order(auto&& val, filter<F>&& f, auto&&... fs) {
//        return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//    }
//
//    template <typename F>
//    auto compute_fs_reverse_order(auto&& val, until<F>&& f, auto&&... fs) {
//        return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//    }
//
//    auto compute_fs_reverse_order(auto&& val, take&& f, auto&&... fs) {
//        return compute_fs_reverse_order(Forward(val), into<std::vector>{}, Forward(f), Forward(fs)...);
//    }
//
//    template <typename F, typename V>
//    auto compute_fs_reverse_order(auto&& val, fold<F, V>&& f) {
//        auto res = f.v;
//        for (auto& e : val)
//            res = f.f(res, e);
//        return res;
//    }
//
//    template <typename F, typename V>
//    auto compute_fs_reverse_order(auto&& val, fold<F, V>&& f, auto&&... fs) {
//        auto res = f.v;
//        auto arg_to_apply_vertically_on = prepare_vertical(Forward(val), fs...);
//        for (auto& e : arg_to_apply_vertically_on) {
//            auto [next, kg] = vertically_apply(e, Forward(fs)...);
//            if (!kg)
//                break;
//            if (next.has_value())
//                res = f.f(res, next.value());
//        }
//        return res;
//    }
//
//    auto compute_fs_reverse_order(auto&& val, into<std::vector>&&) {
//        std::vector<decltype(val)::value_type> res;
//        res.reserve(val.size());
//        for (auto& e : val)
//            res.push_back(e);
//        return res;
//    }
//
//    auto compute_fs_reverse_order(auto&& val, into<std::vector>&&, auto&&... fs) {
//        auto arg_to_apply_vertically_on = prepare_vertical(Forward(val), fs...);
//        using T = decltype(vertically_apply(std::declval<decltype(arg_to_apply_vertically_on)::value_type>(), Forward(fs)...));
//        std::vector<T> res;
//        for (auto& e : arg_to_apply_vertically_on) {
//            auto [next, keep_going] = vertically_apply(e, Forward(fs)...);
//            if (!keep_going)
//                break;
//            if (next.has_value())
//                res.push_back(next.value());
//        }
//        return res;
//    }
//
//    auto vertically_apply(auto&& val) {
//        return std::pair{ std::optional { val }, true };
//    }
//
//    template <typename F>
//    auto vertically_apply(auto&& val, map<F>&& f) {
//        return std::pair{ std::optional { f.f(val) }, true };
//    }
//
//    auto vertically_apply(auto&& val, take&& f) {
//        if (f.n == 0)
//            return std::pair{ decltype(std::optional { val }) { }, false };
//        else {
//            f.n -= 1;
//            return std::pair{ std::optional { val }, true };
//        }
//    }
//
//    template <typename F>
//    auto vertically_apply(auto&& val, filter<F>&& f) {
//        if (f.f(val))
//            return decltype(std::pair{ std::optional { val }, true }){ std::optional{ val }, true };
//        else
//            return decltype(std::pair{ std::optional { val }, true }){ decltype(std::optional{ val }) { }, true };
//    }
//
//    template <typename F>
//    auto vertically_apply(auto&& val, until<F>&& f) {
//        if (f.f(val))
//            return std::pair{ decltype(std::optional { val }) { }, false };
//        else
//            return std::pair{ std::optional { val }, true };
//    }
//}
//
//using inline_fs::compute_fs_natural_order;
//using inline_fs::compute_fs_natural_order_debug;
//using print_ns::is_specialization;
//
//#define FOLD(...) \
//if constexpr (is_into_vec)\
//    res.push_back(__VA_ARGS__);\
//else if constexpr (is_fold)\
//    res = fold.f(res, __VA_ARGS__);
//
//#define isn(n) \
//using t ## n = decltype(op##n);\
//using ismap ## n = is_specialization<t ## n, inline_fs::map>;\
//using istake ## n = std::is_same<t ## n, inline_fs::take>;
//
//auto compute(auto&& seq, auto&& op1, auto&& fold) {
//    constexpr bool is_fold = is_specialization<typename std::decay<decltype(fold)>::type, inline_fs::fold>::value;
//    constexpr bool is_into_vec = std::is_same<typename std::decay<decltype(fold)>::type, inline_fs::into<std::vector>>::value;
//    auto res = [&fold]() {
//        if constexpr (std::is_same<typename std::decay<decltype(fold)>::type, inline_fs::into<std::vector>>::value) {
//            return std::vector<decltype(vertically_apply(std::declval<typename std::decay<decltype(seq)>::type::value_type>(), Forward(op1)).first)>{};
//        }
//        else if constexpr (is_specialization<typename std::decay<decltype(fold)>::type, inline_fs::fold>::value) {
//            return fold.v;
//        }
//    }();
//
//    isn(1);
//
//    for (auto& _0 : seq)
//        if constexpr (ismap1::value) {
//            FOLD(op1.f(_0));
//        }
//        else if constexpr (istake1::value) {
//            if (op1.n > 0) {
//                op1.n -= 1;
//                FOLD(_0);
//            }
//            else
//                break;
//        }
//    return res;
//}
//
//auto compute(auto&& seq, auto&& op1, auto&& op2, auto&& fold) {
//    constexpr bool is_fold = is_specialization<decltype(fold), inline_fs::fold>::value;
//    constexpr bool is_into_vec = std::is_same<typename std::decay<decltype(fold)>::type, inline_fs::into<std::vector>>::value;
//    auto res = [&fold]() {
//        if constexpr (std::is_same<typename std::decay<decltype(fold)>::type, inline_fs::into<std::vector>>::value) {
//            return std::vector<decltype(vertically_apply(std::declval<typename std::decay<decltype(seq)>::type::value_type>(), Forward(op1)).first)>{};
//        }
//        else if constexpr (is_specialization<decltype(fold), inline_fs::fold>::value) {
//            return fold.v;
//        }
//    }();
//
//    isn(1);
//    isn(2);
//
//    for (auto& _0 : seq)
//        if constexpr (ismap1::value) {
//            if constexpr (ismap2::value) {
//                FOLD(op2.f(op1.f(_0)));
//            }
//            else if constexpr (istake2::value) {
//                if (op2.n > 0) {
//                    op2.n -= 1;
//                    FOLD(op1.f(_0));
//                }
//                else
//                    break;
//            }
//        }
//        else if constexpr (istake1::value) {
//            if (op1.n > 0) {
//                op1.n -= 1;
//                if constexpr (ismap2::value) {
//                    FOLD(op2.f(_0));
//                }
//                else if constexpr (istake2::value) {
//                    if (op2.n > 0) {
//                        op2.n -= 1;
//                        FOLD(_0);
//                    }
//                    else
//                        break;
//                }
//            }
//            else
//                break;
//        }
//    return res;
//}