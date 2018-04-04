//
//  variables-json-test.cpp
//  tests
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionjson.hpp>

char const * const JsonExpectation = R"test({
"items": [
{
"_type": "variable",
"is_extern": true,
"is_mutable": false,
"name": "foo",
"type": "const int",
"type_without_qualifiers": "int"
},
{
"_type": "variable",
"is_extern": true,
"is_mutable": true,
"name": "bar",
"type": "void *",
"type_without_qualifiers": "void *"
}
]
})test";

TEST_CASE("json -> variables", "[json]") {
	auto const json = deduction::convert_header_to_json("cases/variables.hpp");
	REQUIRE(json == JsonExpectation);
}
