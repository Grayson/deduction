//
//  field-tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deduction.hpp>
#include <deduction/datatypes/variant.hpp>

TEST_CASE("variables", "[variables]") {
	auto const result = deduction::parse("../cases/variables.hpp");

	auto & foo = mpark::get<deduction::variable>(result.items[0]);
	REQUIRE(foo.name == "foo");
	REQUIRE(foo.full_name == "tests::foo");
	REQUIRE(foo.type == "const int");
	REQUIRE(foo.type_without_qualifiers == "int");
	REQUIRE(foo.is_mutable == false);

	auto & bar = mpark::get<deduction::variable>(result.items[1]);
	REQUIRE(bar.name == "bar");
	REQUIRE(bar.full_name == "tests::bar");
	REQUIRE(bar.type == "void *");
	REQUIRE(bar.type_without_qualifiers == "void *");
	REQUIRE(bar.is_mutable == true);
}

