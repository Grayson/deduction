//
//  versioninfo.cpp
//  tests
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deduction.hpp>

TEST_CASE("verify version info", "[info]") {
	REQUIRE(deduction::version == "0.0.1");
}

