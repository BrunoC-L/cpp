#include "print.h"
#include "functional.h"
#include "generic_functions.h"
#include <sstream>

int main() {
    std::vector<int> v1 = { 1, 2, 3 };

    {
        auto temp = op(v1, // 1, 2, 3
            map{ [](auto x) { return -x; } }); // -1,-2,-3
        println(temp);
    }
    {
        auto temp = op(v1, // 1,2,3
            map{ [](auto x) { return -x; } },  // -1,-2,-3
            map{ [](auto x) { return 2 * x; } },  // -2,-4,-6
            map{ [](auto x) { return std::to_string(x); } }); // "-2", "-4", "-6"
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            filter{ [](auto x) { return x % 2; } }, // 1, 3
            map{ [](auto x) { return 2 * x; } }); // 2, 6
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            filter{ [](auto x) { return x % 2; } }, // 1, 3
            map{ [](auto x) { return 2 * x; } }, // 2, 6
            fold{ [](auto x, auto y) { return x + y; }, 0 }); // 8
        println(temp);
    }
    {
        auto temp = op(5,
            apply{ [](auto x) { return x; } });
        println(temp);
    }
    {
        auto temp = op(5,
            apply{ [](auto x) { return x + 1; } }, // 6
            apply{ [](auto x) {
                std::vector<double> res(x);
                for (int i = 1; i < x; ++i)
                    res[i] = 1.0 / i;
                return res;
            } }                                    // [0, 1, 0.5, 0.333, 0.25, 0.2]
        );
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            filter{ [](auto x) { return x % 2; } }, // 1, 3
            map{ [](auto x) { return 2 * x; } }, // 2, 6
            fold{ [](auto x, auto y) { return x + y; }, 0 }, // 8
            apply{ [](auto x) { return std::to_string(x); } }); // "8"
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            apply{ [](auto x) { return x; } }); // apply: x is the vector
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            apply{ [](auto x) { return x; } },
            apply{ [](auto x) { return x; } },
            apply{ [](auto x) { return x; } });
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            apply{ [](auto x) { return x; } }, // apply: x is the vector
            map{ [](auto x) { return x + 1; } }); // map: x is an element
        println(temp);
    }
    {
        auto temp = op(5,
            apply{ [](auto x) { return x + 1; } }, // 6
            apply{ [](auto x) {
                std::vector<double> res(x);
                for (int i = 1; i < x; ++i)
                    res[i] = 1.0 / i;
                return res;
            } },                                   // [0, 1, 0.5, 0.333, 0.25, 0.2]
            map{ [](auto x) { return 1 - x; } }
        );
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x; } },
            apply{ [](auto x) { return x; } },
            filter{ [](auto x) { return x % 2; } },
            apply{ [](auto x) { return x; } });
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x; } },
            apply{ [](auto x) { return x; } },
            filter{ [](auto x) { return x % 2; } },
            find{ [&](auto x) { return x == 3; } });
        println(temp);
    }
    {
        int count = 0;
        auto sumFirst5 = partial_fold{ [&count](auto x, auto y) {
                if (count++ == 5)
                    return std::optional<std::remove_reference_t<decltype(x + y)>>{};
                else
                    return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
            }, 0 };

        auto temp = op(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sumFirst5);
        println(temp);
    }
    {
        auto sumUntilN = [](int n) {
            return partial_fold{ [n](auto x, auto y) {
                if (y == n)
                    return std::optional<std::remove_reference_t<decltype(x + y)>>{};
                else
                    return std::optional<std::remove_reference_t<decltype(x + y)>>{ x + y };
            }, 0 };
        };

        auto temp = op(
            std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            sumUntilN(7));
        println(temp);
    }
    {
        // take selects first n elements
        auto take = [](int n) {
            int count = 0;
            return partial_filter{ [&count, n](auto x) {
                if (count++ == n)
                    return std::optional<bool>{ std::nullopt };
                else
                    return std::optional<bool>{ true };
            } };
        };
        auto temp = op(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, take(5));
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x; } },
            apply{ [](auto x) { return x; } },
            filter{ [](auto x) { return x % 2; } },
            foreach{ println },
            find{ [](auto x) { return x > 1; } });
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x; } });
        println(temp);
    }
    {
        auto weird_format = []() { return complex_fold{
                [](auto default_value, auto first) { default_value << first; return default_value; },
                [](auto current_value, auto next) { current_value << " : " << next; return current_value; },
                [](auto current_value) { current_value << "}"; return current_value.str(); },
                []() { std::stringstream ss; ss << "{"; return ss; }()
        }; };
        {
            auto temp = op(v1,// 1,2,3
                futil::conversions::maps::to_string,
                futil::conversions::maps::to_string,
                futil::conversions::maps::to_string,// "1", "2", "3"
                weird_format()); // {1 : 2 : 3}
            println(temp);
        }
        {
            auto temp = op(std::vector<int>{},
                futil::conversions::maps::to_string,
                weird_format()); // {}
            println(temp);
        }
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x * x; } }, // 1,4,9
            futil::manipulations::maps::index_from_zero());
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x * x; } }, // 1,4,9
            futil::manipulations::maps::index_from(1));
        println(temp);
    }
    {
        auto temp = op(v1,// 1,2,3
            map{ [](auto x) { return x * x; } }, // 1,4,9
            futil::manipulations::maps::reverse_index_from(1));
        println(temp);
    }

    return 0;
}
