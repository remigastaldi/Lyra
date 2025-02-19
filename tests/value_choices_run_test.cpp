/*
Copyright Rene Rivera 2019
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include <lyra/lyra.hpp>
#include "mini_test.hpp"

int main()
{
	using namespace lyra;
	bfg::mini_test::scope test;

	{
		std::string choice;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices("one", "two", "other");
		auto result = p.parse( { "TestApp", "-c", "two" } );
		test
			(REQUIRE(result))
			(REQUIRE(choice == "two"));
	}
	{
		std::string choice;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices("one", "two", "other");
		auto result = p.parse( { "TestApp", "-c", "foo" } );
		test
			(REQUIRE(!result));
	}
	{
		int choice = 0;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices(1, 2, 3);
		auto result = p.parse( { "TestApp", "-c", "2" } );
		test
			(REQUIRE(result))
			(REQUIRE(choice == 2));
	}
	{
		int choice = 0;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices(1, 2, 3);
		auto result = p.parse( { "TestApp", "-c", "5" } );
		test
			(REQUIRE(!result))
			(REQUIRE(choice == 0));
	}
	{
		int choice = 20;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices([](int value) -> bool { return 10 <= value && value <= 20; });
		auto result = p.parse( { "TestApp", "-c", "15" } );
		test
			(REQUIRE(result))
			(REQUIRE(choice == 15));
	}
	{
		int choice = 20;
		auto p = opt(choice, "choice")["-c"]["--choice"]("the choice")
			.choices([](int value) -> bool { return 10 <= value && value <= 20; });
		auto result = p.parse( { "TestApp", "-c", "40" } );
		test
			(REQUIRE(!result))
			(REQUIRE(choice == 20));
	}
	{
		std::string choice;
		auto p = arg(choice, "choice")("the choice")
			.choices("walk", "run", "jump");
		auto result = p.parse( { "TestApp", "run" } );
		test
			(REQUIRE(result))
			(REQUIRE(choice == "run"));
	}

	return test;
}
