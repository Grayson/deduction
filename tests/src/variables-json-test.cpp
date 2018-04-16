//
//  variables-json-test.cpp
//  tests
//
//  Created by Grayson Hansard on 3/31/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deductionjson.hpp>
#include <deduction/json/json.hpp>
#include <deduction/json/parse-result.hpp>

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
],
"metadata": {
"file": "../cases/variables.hpp",
"version": "0.0.1"
}
})test";

TEST_CASE("variables -> json", "[json/variable]") {
	auto const json = deduction::convert_header_to_json("../cases/variables.hpp");
	REQUIRE(json == JsonExpectation);
}

TEST_CASE("json -> variables", "[json/variable]") {
	auto const json = nlohmann::json::parse(JsonExpectation);
	auto const results = json.at("items").get<deduction::parse_result>();
	REQUIRE(results.items.size() == 2);

	auto const & foo = mpark::get<deduction::variable>(results.items[0]);
	REQUIRE(foo.name == "foo");
	REQUIRE(foo.type == "const int");
	REQUIRE(foo.type_without_qualifiers == "int");
	REQUIRE(foo.is_extern == true);
	REQUIRE(foo.is_mutable == false);

	auto const & bar = mpark::get<deduction::variable>(results.items[1]);
	REQUIRE(bar.name == "bar");
	REQUIRE(bar.type == "void *");
	REQUIRE(bar.type_without_qualifiers == "void *");
	REQUIRE(bar.is_extern == true);
	REQUIRE(bar.is_mutable == true);
}
