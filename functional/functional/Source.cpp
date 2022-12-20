#include "print.h"
#include "functional.h"

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

    return 0;
}
