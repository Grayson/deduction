//
//  field-tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionlib.hpp>
#include <deduction/variant.hpp>

TEST_CASE("variables", "[variables]") {
	auto const result = deduction::parse("cases/variables.hpp");

	auto & foo = mpark::get<deduction::variable>(result.items[0]);
	REQUIRE(foo.name == "foo");
	REQUIRE(foo.type == "const int");
	REQUIRE(foo.is_mutable == false);

	auto & bar = mpark::get<deduction::variable>(result.items[1]);
	REQUIRE(bar.name == "bar");
	REQUIRE(bar.type == "void *");
	REQUIRE(bar.is_mutable == true);
}

