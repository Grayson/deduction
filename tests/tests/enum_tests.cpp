//
//  enum_tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/8/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionlib.hpp>

TEST_CASE("simple enum", "[enum]") {
	REQUIRE(!deduction::parse("cases/enum.hpp").items.empty());
}
