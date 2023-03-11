#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};
template <typename Stream>
decltype(auto) _serialize_into(Stream&& stream, auto&& t);

template <size_t idx>
decltype(auto) g(auto&& stream, auto&& t) {
	return _serialize_into(std::forward<decltype(stream)>(stream), std::forward<decltype(std::get<idx>(t))>(std::get<idx>(t)));
}

template <std::size_t... Idx>
decltype(auto) f(std::index_sequence<Idx...>, auto&& stream, auto&& t) {
	//(_serialize_into(std::forward<decltype(stream)>(stream), std::get<Idx>(t))...);
	(g<Idx>(std::forward<decltype(stream)>(stream), std::forward<decltype(t)>(t)), ...);
	return stream;
}

template <typename Stream>
decltype(auto) _serialize_into(Stream&& stream, auto&& t) {
	if constexpr (is_specialization<std::decay_t<decltype(t)>, std::tuple>::value) {
		constexpr int size = std::tuple_size<std::decay_t<decltype(t)>>::value;
		constexpr auto iseq = std::make_index_sequence<size>();
		return f(iseq, std::forward<decltype(stream)>(stream), std::forward<decltype(t)>(t));
	}
	else
		return stream << t;
}

template <typename... Ts>
struct Serializable {
	std::tuple<Ts...> data;

	Serializable(auto&&... ts) : data(std::forward<decltype(ts)>(ts)...) {};

	template <typename Stream>
	decltype(auto) serialize_into(Stream&& stream) const {
		return _serialize_into(stream, data);
	}
};

int main() {
	std::stringstream buffer;

	Serializable<int> seven(7);
	seven.serialize_into(buffer);

	buffer << "\n";

	Serializable<int, std::string> seri(2, std::string("seri"));
	seri.serialize_into(buffer);

	std::cout << buffer.str();
}
