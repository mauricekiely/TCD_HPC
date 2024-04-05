/**
 * @file is_floating.cc
 * @brief  Toy example to show how you might implement a class/struct to provide some type trait information
 * @author R. Morrin
 * @version 1.0
 * @date 2024-03-09
 */

#include <iostream>
#include <iomanip>

template <typename T>
struct is_floating{
	static const bool value {false};
};

template <>
struct is_floating<float> {
    static const bool value {true};
};

template <>
struct is_floating<double> {
    static const bool value {true};
};

int main()
{
	auto a {1.0};
	auto b {2};
	auto c{3.4f};

	std::cout <<  std::boolalpha 
		  << "a:\t" << is_floating<decltype(a)>::value << '\n'
		  << "b:\t" << is_floating<decltype(b)>::value << '\n'
		  << "c:\t" << is_floating<decltype(c)>::value << '\n';

	return 0;
}
