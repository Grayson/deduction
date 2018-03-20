//
//  function-pointer-tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/12/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionlib.hpp>
#include <deduction/variant.hpp>

TEST_CASE("using alias", "[function pointer]") {
	auto const result = deduction::parse("cases/function-pointer.hpp");
	auto & alias = mpark::get<deduction::alias>(result.items[0]);

	REQUIRE(alias.name == "FooCallback");
	REQUIRE(alias.underlying_type == "bool (*)(int)");
}
