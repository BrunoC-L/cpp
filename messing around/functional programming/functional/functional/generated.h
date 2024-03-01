#pragma once
#include <vector>

namespace generated {

    struct InputTypes {
        struct Sequence { using Seq = void; };
        struct Element { using Elem = void; };
    };

    template <typename F>
    struct map {
        F f;
    };

    template <typename F>
    struct foreach {
        F f;
    };

    template <typename F>
    struct filter {
        F f;
    };

    template <typename F>
    struct take_while {
        F f;
    };

    template <typename F>
    struct take_once {
        F f;
        bool v = false;
    };

    struct take {
        mutable int n;
    };



    template <typename F, typename InitialValue>
    struct fold {
        F f;
        InitialValue v;
    };

    template <template <typename...> typename Container>
    struct into {
    };

    template <typename F>
    struct find {
        F f;
    };

    template <typename F>
    struct apply {
        F f;
    };

    auto compute(auto&& seq, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    res.push_back(value_0);
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    res = f0.f(res, value_0);
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                res.push_back(value_0);
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
            int value_1{};
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                value_1 = f1.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                res = f0.f(res, value_0);
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const auto& f6, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_6 = f6.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_5)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_1 = f6.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_0)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const auto& f6, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_6 = f6.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_5)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_1 = f6.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_0)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const auto& f6, const auto& f7, const into<std::vector>& f0) {
		auto res = std::vector<typename std::decay<decltype(seq)>::type::value_type>{};

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_6 = f6.f(value_5);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_7 = f7.f(value_6);
                res.push_back(value_7);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_6)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_6)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_6)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_6);
                res.push_back(value_6);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_5)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_5);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res.push_back(value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res.push_back(value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res.push_back(value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res.push_back(value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res.push_back(value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res.push_back(value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res.push_back(value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res.push_back(value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_1 = f6.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res.push_back(value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res.push_back(value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_0)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_1 = f7.f(value_0);
                res.push_back(value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_0)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_0);
                res.push_back(value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
    template <typename K, typename V>
    auto compute(auto&& seq, const auto& f1, const auto& f2, const auto& f3, const auto& f4, const auto& f5, const auto& f6, const auto& f7, const fold<K, V>& f0) {
		auto res = f0.v;

		for (auto& value_0 : seq) {
    
            if constexpr (is_specialization<std::decay<decltype(f1)>::type, map>::value) {
                auto value_1 = f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_2 = f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_3 = f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_4 = f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_5 = f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_6 = f6.f(value_5);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_7 = f7.f(value_6);
                res = f0.f(res, value_7);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_6)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_6)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_6)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_6);
                res = f0.f(res, value_6);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_5)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_5);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_4)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_3)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_2)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_1)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_once>::value)
                    if (!f1.v && !f1.f(value_0)) continue; else f1.v = true;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, take_while>::value)
                    if (!f1.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f1)>::type, take>::value)
                    if (f1.n > 0) f1.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, filter>::value)
                    if (!f1.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f1)>::type, foreach>::value)
                    f1.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f2)>::type, map>::value) {
                auto value_1 = f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_2 = f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_3 = f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_4 = f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_5 = f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_6 = f7.f(value_5);
                res = f0.f(res, value_6);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_5)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_5)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_5)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_5);
                res = f0.f(res, value_5);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_4)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_4);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_3)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_2)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_1)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_once>::value)
                    if (!f2.v && !f2.f(value_0)) continue; else f2.v = true;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, take_while>::value)
                    if (!f2.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f2)>::type, take>::value)
                    if (f2.n > 0) f2.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, filter>::value)
                    if (!f2.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f2)>::type, foreach>::value)
                    f2.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f3)>::type, map>::value) {
                auto value_1 = f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_2 = f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_3 = f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_4 = f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_5 = f7.f(value_4);
                res = f0.f(res, value_5);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_4)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_4)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_4)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_4);
                res = f0.f(res, value_4);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_3)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_3);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_2)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_1)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_once>::value)
                    if (!f3.v && !f3.f(value_0)) continue; else f3.v = true;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, take_while>::value)
                    if (!f3.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f3)>::type, take>::value)
                    if (f3.n > 0) f3.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, filter>::value)
                    if (!f3.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f3)>::type, foreach>::value)
                    f3.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f4)>::type, map>::value) {
                auto value_1 = f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_2 = f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_3 = f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_4 = f7.f(value_3);
                res = f0.f(res, value_4);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_3)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_3)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_3)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_3);
                res = f0.f(res, value_3);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_2)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_2);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_1)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_once>::value)
                    if (!f4.v && !f4.f(value_0)) continue; else f4.v = true;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, take_while>::value)
                    if (!f4.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f4)>::type, take>::value)
                    if (f4.n > 0) f4.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, filter>::value)
                    if (!f4.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f4)>::type, foreach>::value)
                    f4.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f5)>::type, map>::value) {
                auto value_1 = f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_2 = f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_3 = f7.f(value_2);
                res = f0.f(res, value_3);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_2)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_2)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_2)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_2);
                res = f0.f(res, value_2);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_1)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_1);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_once>::value)
                    if (!f5.v && !f5.f(value_0)) continue; else f5.v = true;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, take_while>::value)
                    if (!f5.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f5)>::type, take>::value)
                    if (f5.n > 0) f5.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, filter>::value)
                    if (!f5.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f5)>::type, foreach>::value)
                    f5.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f6)>::type, map>::value) {
                auto value_1 = f6.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_2 = f7.f(value_1);
                res = f0.f(res, value_2);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_1)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_1)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_1)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_1);
                res = f0.f(res, value_1);
            }
        
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_once>::value)
                    if (!f6.v && !f6.f(value_0)) continue; else f6.v = true;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, take_while>::value)
                    if (!f6.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f6)>::type, take>::value)
                    if (f6.n > 0) f6.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, filter>::value)
                    if (!f6.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f6)>::type, foreach>::value)
                    f6.f(value_0);
                
            if constexpr (is_specialization<std::decay<decltype(f7)>::type, map>::value) {
                auto value_1 = f7.f(value_0);
                res = f0.f(res, value_1);
            }
            else {
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_once>::value)
                    if (!f7.v && !f7.f(value_0)) continue; else f7.v = true;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, take_while>::value)
                    if (!f7.f(value_0)) break;
                if constexpr (std::is_same<std::decay<decltype(f7)>::type, take>::value)
                    if (f7.n > 0) f7.n -= 1; else break;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, filter>::value)
                    if (!f7.f(value_0)) continue;
                if constexpr (is_specialization<std::decay<decltype(f7)>::type, foreach>::value)
                    f7.f(value_0);
                res = f0.f(res, value_0);
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
            }
        
		}
		return res;
	}
    
}