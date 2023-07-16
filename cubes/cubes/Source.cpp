#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <unordered_set>

namespace R3 {
    struct X {};
    struct Y {};
    struct Z {};
}

template <unsigned Dim>
struct Coordinate {
    std::array<unsigned, Dim> data{};
    auto neighboring_coordinates() const {
        if constexpr (Dim == 2) {
            return std::array<Coordinate, 4> {
                Coordinate{ data.at(0) + 1, data.at(1) },
                Coordinate{ data.at(0) - 1, data.at(1) },
                Coordinate{ data.at(0), data.at(1) + 1 },
                Coordinate{ data.at(0), data.at(1) - 1 },
            };
        }
        else if constexpr (Dim == 3) {
            return std::array<Coordinate, 6> {
                Coordinate{ data.at(0) + 1, data.at(1), data.at(2) },
                Coordinate{ data.at(0) - 1, data.at(1), data.at(2) },
                Coordinate{ data.at(0), data.at(1) + 1, data.at(2) },
                Coordinate{ data.at(0), data.at(1) - 1, data.at(2) },
                Coordinate{ data.at(0), data.at(1), data.at(2) + 1 },
                Coordinate{ data.at(0), data.at(1), data.at(2) - 1 },
            };
        }
    }

    template <unsigned r>
    Coordinate rotate(const Coordinate& bounding_box) const {
        if constexpr (Dim == 2) {
            if constexpr (r == 1)
                return Coordinate{ std::array<unsigned, Dim>{ data.at(1), bounding_box.data.at(0) - 1 - data.at(0) } };
            else
                return rotate<1>(bounding_box).rotate<r - 1>(Coordinate<Dim>{ std::array<unsigned, 2>{ bounding_box.data.at(1), bounding_box.data.at(0) } });
        }
    }

    template <typename R>
    Coordinate rotate3(const Coordinate& bounding_box) const {
        if constexpr (std::is_same_v<R, R3::X>)
            return Coordinate{ std::array<unsigned, Dim>{ data.at(0), data.at(2), bounding_box.data.at(2) - 1 - data.at(1) } };
        else if constexpr (std::is_same_v<R, R3::Y>)
            return Coordinate{ std::array<unsigned, Dim>{ bounding_box.data.at(0) - 1 - data.at(2), data.at(1), data.at(0) } };
        else
            return Coordinate{ std::array<unsigned, Dim>{ data.at(1), bounding_box.data.at(1) - 1 - data.at(0), data.at(2) } };
    }

    template <typename R, typename R2, typename... Rs>
    Coordinate rotate3(const Coordinate& bounding_box) const {
        if constexpr (std::is_same_v<R, R3::X>)
            return rotate3<R>(bounding_box)
                        .rotate3<R2, Rs...>(
                            Coordinate<Dim>{ 
                                std::array<unsigned, 3>{
                                    bounding_box.data.at(0),
                                    bounding_box.data.at(2),
                                    bounding_box.data.at(1) 
                                } 
                            });
        else if constexpr (std::is_same_v<R, R3::Y>)
            return rotate3<R>(bounding_box)
                        .rotate3<R2, Rs...>(
                            Coordinate<Dim>{
                                std::array<unsigned, 3>{
                                    bounding_box.data.at(2),
                                    bounding_box.data.at(1),
                                    bounding_box.data.at(0)
                                }
                            });
        else
            return rotate3<R>(bounding_box)
                        .rotate3<R2, Rs...>(
                            Coordinate<Dim>{
                                std::array<unsigned, 3>{
                                    bounding_box.data.at(1),
                                    bounding_box.data.at(0),
                                    bounding_box.data.at(2)
                                }
                            });
    }

    struct Hash {
        size_t operator()(const Coordinate& sp) const {
            if constexpr (Dim == 2) {
                constexpr auto maxlen = 100;
                return maxlen * sp.data.at(0) + sp.data.at(1);
            }
            else {
                constexpr auto maxlen = 100;
                return maxlen * maxlen * sp.data.at(0) + maxlen * sp.data.at(1) + sp.data.at(2);
            }
        }
    };

    Coordinate& operator=(const Coordinate& other) {
        data = other.data;
        return *this;
    }

    friend auto operator<=>(const Coordinate& first, const Coordinate& second) = default;
};

// https://stackoverflow.com/a/59420788/10945691
template<typename T>
static constexpr inline T pown(T x, unsigned p) {
    T result = 1;

    while (p) {
        if (p & 0x1) {
            result *= x;
        }
        x *= x;
        p >>= 1;
    }

    return result;
}

template <unsigned Len, unsigned Dim>
struct Space {
    Coordinate<Dim> bounding_box;
    std::array<bool, pown(Len, Dim)> space = { 0 };

    bool index(const Coordinate<Dim>& coordinate) const {
        if constexpr (Dim == 2) {
            return space[coordinate.data.at(0) * Len + coordinate.data.at(1)];
        }
        else if constexpr (Dim == 3) {
            return space[coordinate.data.at(0) * Len * Len + coordinate.data.at(1) * Len + coordinate.data.at(2)];
        }
    }

    void insert(const Coordinate<Dim>& coordinate) {
        if constexpr (Dim == 2) {
            space[coordinate.data.at(0) * Len + coordinate.data.at(1)] = true;
        }
        else if constexpr (Dim == 3) {
            space[coordinate.data.at(0) * Len * Len + coordinate.data.at(1) * Len + coordinate.data.at(2)] = true;
        }
    }
};

template <unsigned Len, unsigned Dim>
struct Configuration {
    using Sequence = std::array<Coordinate<Dim>, Len>;
    mutable Sequence data;
    Coordinate<Dim> bounding_box;

    template <unsigned _Len>
    Space<_Len, Dim> as_space() const {
        Space<_Len, Dim> space;
        for (const Coordinate<Dim>& c : data)
            space.insert(c);
        space.bounding_box = bounding_box;
        return space;
    }

    Configuration<Len + 1, Dim> append(const Coordinate<Dim>& c) const {
        Configuration<Len + 1, Dim> res{};

        // if new coordinate is below zero on some axis
        for (unsigned d = 0; d < Dim; ++d)
            if (c.data.at(d) == -1) {
                res.bounding_box = bounding_box;
                // the new bounding box is pushed by one along that axis
                res.bounding_box.data.at(d) += 1;
                for (unsigned i = 0; i < Len; ++i) {
                    res.data[i] = data[i];
                    // and so are all the points
                    res.data[i].data.at(d) += 1;
                }
                res.data[Len] = c;
                // and the new point is placed at  zero instread of negative 1
                res.data[Len].data.at(d) += 1;
                std::sort(res.data.begin(), res.data.end());
                return res;
            }
        // else

        // all the data stays in place
        for (unsigned i = 0; i < Len; ++i)
            res.data[i] = data[i];
        // as well as the new coordinate
        res.data[Len] = c;
        std::sort(res.data.begin(), res.data.end());

        res.bounding_box = bounding_box;
        // and we check if the bounding box has to be updated if the new coordinate is far enough
        for (unsigned d = 0; d < Dim; ++d)
            if (c.data.at(d) == res.bounding_box.data.at(d))
                res.bounding_box.data.at(d) += 1;
        return res;
    }

    template <unsigned r>
    Configuration rotation() const {
        Configuration<Len, Dim> res{};
        if constexpr (r % 2 == 0)
            res.bounding_box = bounding_box;
        else
            res.bounding_box = { bounding_box.data.at(1), bounding_box.data.at(0) };
        for (unsigned i = 0; i < Len; ++i)
            res.data.at(i) = data.at(i).rotate<r>(bounding_box);
        std::sort(res.data.begin(), res.data.end());
        return res;
    }

    template <typename R>
    Configuration rotation3() const {
        Configuration<Len, Dim> res{};
        if constexpr (std::is_same_v<R, R3::X>)
            res.bounding_box = { bounding_box.data.at(0), bounding_box.data.at(2), bounding_box.data.at(1) };
        else if constexpr (std::is_same_v<R, R3::Y>)
            res.bounding_box = { bounding_box.data.at(2), bounding_box.data.at(1), bounding_box.data.at(0) };
        else
            res.bounding_box = { bounding_box.data.at(1), bounding_box.data.at(0), bounding_box.data.at(2) };
        for (unsigned i = 0; i < Len; ++i)
            res.data.at(i) = data.at(i).rotate3<R>(res.bounding_box);
        std::sort(res.data.begin(), res.data.end());
        return res;
    }

    template <typename R1, typename R2, typename... Rs>
    Configuration rotation3() const {
        return rotation3<R1>().rotation3<R2, Rs...>();
    }

    struct Hash {
        size_t operator()(const Configuration& sp) const {
            using H = Coordinate<Dim>::Hash;
            auto hasher = H{};
            auto hash = hasher(sp.bounding_box);
            for (int i = 0; i < Len; ++i)
                hash = hash ^ (hasher(sp.data.at(i)) << i);
            return hash;
        }
    };
    friend auto operator<=>(const Configuration& first, const Configuration& second) = default;
};

template <unsigned Len, unsigned Dim, unsigned CurLen = Len>
auto generate_polycubes() {
    using C = Configuration<CurLen, Dim>;
    std::vector<C> res;

    if constexpr (CurLen == 1) {
        C val{};
        for (unsigned i = 0; i < Dim; ++i)
            val.bounding_box.data.at(i) += 1;
        res.push_back(val);
        return res;
    }
    else {
        auto prev = generate_polycubes<Len, Dim, CurLen - 1>();
        std::cout << "iterating through " << prev.size() << "\n";
        std::unordered_set<C, typename C::Hash> used;
        if constexpr (Dim == 2) {
            res.reserve(prev.size() * 4);
            used.reserve(prev.size() * 4);
        }
        else {
            res.reserve(prev.size() * 8);
            used.reserve(prev.size() * 8);
        }
        for (const auto& configuration : prev) {
            auto space = configuration.as_space<Len>();
            for (const Coordinate<Dim>& c : configuration.data) {
                auto neighboring_coordinates = c.neighboring_coordinates();
                for (const Coordinate<Dim>& n : neighboring_coordinates) {
                    bool hasNegative = false;
                    if constexpr (Dim == 2) {
                        hasNegative =   n.data.at(0) == -1 ||
                                        n.data.at(1) == -1;
                    }
                    else {
                        hasNegative =   n.data.at(0) == -1 ||
                                        n.data.at(1) == -1 ||
                                        n.data.at(2) == -1;
                    }
                    if (hasNegative || !space.index(n)) {
                        if (!hasNegative)
                            space.insert(n);
                        auto new_configuration = configuration.append(n);
                        if constexpr (Dim == 2) {
                            if (used.contains(new_configuration) ||
                                used.contains(new_configuration.rotation<1>()) ||
                                used.contains(new_configuration.rotation<2>()) ||
                                used.contains(new_configuration.rotation<3>()))
                                continue;
                        }
                        else {
                            if (used.contains(new_configuration) ||
                                used.contains(new_configuration.rotation3<R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::Y, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::X, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::Y, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::Y, R3::Y>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::X, R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::Y, R3::Y, R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::X, R3::X, R3::Y, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::X, R3::X, R3::X>()) ||
                                used.contains(new_configuration.rotation3<R3::X, R3::Y, R3::Y, R3::Y, R3::X>())
                                )
                                continue;
                        }
                        used.insert(new_configuration);
                        res.push_back(new_configuration);
                    }
                }
            }
        }
        return res;
    }
}

unsigned main() {
    constexpr unsigned depth2 = 16;
    constexpr unsigned depth3 = 11;
    {
        auto t1 = std::chrono::steady_clock::now();
        auto all_cubes = generate_polycubes<depth2, 2>();
        auto t2 = std::chrono::steady_clock::now();
        // 16: 26152418 calculated in 197.564s (reached 9.8GB)
        std::cout << depth2 << ": " << all_cubes.size() << " calculated in " << (t2 - t1).count() / 1000000000.0 << "s\n";
    }
    {
        auto t1 = std::chrono::steady_clock::now();
        auto all_cubes = generate_polycubes<depth3, 3>();
        auto t2 = std::chrono::steady_clock::now();
        // 11: 2522522 calculated in 60.6725s (reached 1GB)
        std::cout << depth3 << ": " << all_cubes.size() << " calculated in " << (t2 - t1).count() / 1000000000.0 << "s\n";
    }
    return 0;
}
