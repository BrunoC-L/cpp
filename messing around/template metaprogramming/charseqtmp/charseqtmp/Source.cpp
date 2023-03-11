#include <iostream>
#include <algorithm>
#include <string>

template<size_t N>
struct StringLiteral {
    char value[N];
    constexpr StringLiteral(const char(&str)[N]) {
        std::copy_n(str, N, value);
    }
};

template <StringLiteral T>
struct String {
    static constexpr std::string str() {
        return T.value;
    }
};

template <typename... Strings>
struct JoinedString {
    static constexpr std::string str() {
        return (Strings::str() + ...);
    }
};

template <typename Delim, typename String, typename... Strings>
struct DelimJoinedString {
    static constexpr std::string str() {
        if constexpr (sizeof...(Strings))
            return JoinedString<String, Delim, DelimJoinedString<Delim, Strings...>>::str();
        else
            return String::str();
    }
};

int main() {
    // "123"
    using s123 = String<"123">;
    std::cout << s123::str() << "\n";

    // "abc"
    using abc = String<"abc">;
    std::cout << abc::str() << "\n";

    // "abc123abc123"
    using abc123abc123 = JoinedString<abc, s123, abc, s123>;
    std::cout << abc123abc123::str() << "\n";

    // "abc, 123"
    using abccomma123 = DelimJoinedString<String<", ">, abc, s123>;
    std::cout << abccomma123::str() << "\n";

    // "abc, 123, 123, abc"
    using commaabc123123abc = DelimJoinedString<String<", ">, abc, s123, s123, abc>;
    std::cout << commaabc123123abc::str() << "\n";
    return 0;
}
