//
//  function-tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/10/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deduction.hpp>
#include <deduction/datatypes/variant.hpp>

TEST_CASE("free functions", "[function]") {
	auto const result = deduction::parse("../cases/function.hpp");
	REQUIRE(result.items.size() == 5);

	// void foo();
	auto const & voidFoo = mpark::get<deduction::function>(result.items[0]);
	REQUIRE(voidFoo.name == "foo");
	REQUIRE(voidFoo.full_name == "foo");
	REQUIRE(voidFoo.parameters.size() == 0);
	REQUIRE(voidFoo.return_type == "void");

	//	void foo(int i);
	auto const & voidFooWithInt = mpark::get<deduction::function>(result.items[1]);
	REQUIRE(voidFooWithInt.name == "foo");
	REQUIRE(voidFooWithInt.full_name == "foo");
	REQUIRE(voidFooWithInt.parameters.size() == 1);
	REQUIRE(voidFooWithInt.parameters[0].name == "i");
	REQUIRE(voidFooWithInt.parameters[0].type == "int");
	REQUIRE(voidFooWithInt.return_type == "void");

	//	void foo(double);
	auto const & voidFooWithDouble = mpark::get<deduction::function>(result.items[2]);
	REQUIRE(voidFooWithDouble.name == "foo");
	REQUIRE(voidFooWithDouble.full_name == "foo");
	REQUIRE(voidFooWithDouble.parameters.size() == 1);
	REQUIRE(voidFooWithDouble.parameters[0].name == "");
	REQUIRE(voidFooWithDouble.parameters[0].type == "double");
	REQUIRE(voidFooWithDouble.return_type == "void");

	//	int bar();
	auto const & intBar = mpark::get<deduction::function>(result.items[3]);
	REQUIRE(intBar.name == "bar");
	REQUIRE(intBar.full_name == "bar");
	REQUIRE(intBar.parameters.size() == 0);
	REQUIRE(intBar.return_type == "int");

	//	int bar(int i, double d);
	auto const & intBarWithIntAndDouble = mpark::get<deduction::function>(result.items[4]);
	REQUIRE(intBarWithIntAndDouble.name == "bar");
	REQUIRE(intBarWithIntAndDouble.full_name == "bar");
	REQUIRE(intBarWithIntAndDouble.parameters.size() == 2);
	REQUIRE(intBarWithIntAndDouble.parameters[0].name == "i");
	REQUIRE(intBarWithIntAndDouble.parameters[0].type == "int");
	REQUIRE(intBarWithIntAndDouble.parameters[1].name == "d");
	REQUIRE(intBarWithIntAndDouble.parameters[1].type == "double");
	REQUIRE(intBarWithIntAndDouble.return_type == "int");
}
