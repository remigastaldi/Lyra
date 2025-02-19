/*
Copyright Rene Rivera 2019
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

// tag::part1[]
#include <iostream>
#include <lyra/lyra.hpp>

int main(int argc, const char** argv)
{
	std::string choice;
	// Ex: <exe> --choice=red
	auto cli
		= lyra::opt(choice, "-c")["--choice"]
			.choices("red", "green", "blue");
	auto result = cli.parse({ argc, argv });
	if (result)
	{
		std::cout << "Your preferred color is " << choice << "\n";
	}
	else
	{
		std::cerr << result.errorMessage() << "\n";
	}
}
// end::part1[]
