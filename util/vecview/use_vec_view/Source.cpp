#include "Header.h"
#include <iostream>

int main() {
	{
		int a = 1;
		const int b = 2;
		vecview::ViewOf<int> auto v1 = vecview::element(a);
		vecview::ViewOf<int> auto v2 = vecview::element((const int&)b);
		vecview::ViewOf<int> auto v3 = vecview::element(3);
		const vecview::ViewOf<int> auto v4 = vecview::element(4);


		for (const int& i : v1) {
			std::cout << i << "\n";
		}

		for (const int& i : v2) {
			std::cout << i << "\n";
		}

		for (const int& i : v3) {
			std::cout << i << "\n";
		}

		for (const int& i : v4) {
			std::cout << i << "\n";
		}

		for (const int& i : vecview::element(5)) {
			std::cout << i << "\n";
		}
	}
	std::cout << "\n";
	std::cout << "\n";
	{
		int a = 1;
		const int b = 2;
		vecview::ViewOf<int> auto v1 = vecview::element(a);
		vecview::ViewOf<int> auto v3 = vecview::element(3);
		auto v5 = vecview::join(vecview::element(6));
		auto v6 = vecview::join(vecview::element(7), vecview::element(8));
		for (const int& i : v5) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		for (const int& i : v6) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		for (const int& i : vecview::join(vecview::element(9))) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		for (const int& i : vecview::join(vecview::element(9), v1, v3, vecview::element(10))) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		for (const int& i : vecview::join(vecview::join(vecview::element(11)))) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
	}
	{
		auto u = vecview::join(std::vector<int>{12, 13, 14});
		for (const int& i : u) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		auto u2 = vecview::join(std::vector<int>{15, 16, 17});
		vecview::view_tuple<int, vecview::view_tuple<int, std::vector<int>>&> u3 = vecview::join(u2);
		for (const int& i : vecview::join(u2)) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		for (const int& i : vecview::join(u, vecview::element(666), u2, vecview::element(777), std::vector<int>{8, 8, 8})) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
		auto v = vecview::join(u, vecview::element(666), u2, vecview::element(777), std::vector<int>{8, 8, 8});
		if (v.size() != u.size() + 1 + u2.size() + 1 + 3) {
			abort();
		}
		for (const int& i : v) {
			std::cout << i << ", ";
		}
		std::cout << "\n";
	}
	return 0;
}
