//
//  struct-json-test.cpp
//  tests
//
//  Created by Grayson Hansard on 4/3/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionjson.hpp>

TEST_CASE("json -> struct", "[json]") {
	char const * const StructJsonExpectation = R"test({
"items": [
{
"_type": "struct",
"constructors": [
{
"full_name": "foo::foo",
"name": "foo",
"parameters": []
},
{
"full_name": "foo::foo",
"name": "foo",
"parameters": [
{
"name": "grault",
"type": "int"
}
]
}
],
"fields": [
{
"is_mutable": true,
"name": "bar",
"type": "int"
},
{
"is_mutable": false,
"name": "corge",
"type": "const int"
}
],
"full_name": "foo",
"methods": [
{
"full_name": "foo::baz",
"name": "baz",
"parameters": [
{
"name": "quux",
"type": "bool"
},
{
"name": "quuz",
"type": "void *"
}
],
"return_type": "double"
},
{
"full_name": "foo::garply",
"name": "garply",
"parameters": [],
"return_type": "bool"
}
],
"name": "foo"
}
]
})test";

	auto const json = deduction::convert_header_to_json("../cases/struct.hpp");
	REQUIRE(json == StructJsonExpectation);
}

TEST_CASE("namespaced struct -> json", "[json]") {
char const * const NamespacedStructJsonTest = R"test({
"items": [
{
"_type": "struct",
"constructors": [],
"fields": [
{
"is_mutable": true,
"name": "bar",
"type": "int"
}
],
"full_name": "tests::foo",
"methods": [],
"name": "foo"
}
]
})test";
	auto const json = deduction::convert_header_to_json("../cases/namespaced-struct.hpp");
	REQUIRE(json == NamespacedStructJsonTest);
}
