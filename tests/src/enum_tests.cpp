//
//  enum_tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/8/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deduction.hpp>
#include <deduction/datatypes/variant.hpp>
#include <deduction/deductionjson.hpp>
#include <deduction/json/json.hpp>
#include <deduction/json/parse-result.hpp>

TEST_CASE("simple enum", "[enum]") {
	auto const result = deduction::parse("../cases/enum.hpp");
	REQUIRE(result.items.size() == 1);

	auto const & en = mpark::get<deduction::enumeration>(result.items[0]);
	REQUIRE(en.name == "Foo");

	REQUIRE(en.case_labels[0].name == "bar");
	REQUIRE(en.case_labels[1].name == "baz");
	REQUIRE(en.case_labels[2].name == "quux");

	REQUIRE(en.case_labels[0].full_name == "Foo::bar");
	REQUIRE(en.case_labels[1].full_name == "Foo::baz");
	REQUIRE(en.case_labels[2].full_name == "Foo::quux");
}

TEST_CASE("enum class", "[enum]") {
	auto const result = deduction::parse("../cases/enum-class.hpp");
	REQUIRE(result.items.size() == 1);

	auto const & en = mpark::get<deduction::enumeration>(result.items[0]);
	REQUIRE(en.name == "Foo");

	REQUIRE(en.case_labels[0].name == "bar");
	REQUIRE(en.case_labels[1].name == "baz");
	REQUIRE(en.case_labels[2].name == "quux");

	REQUIRE(en.case_labels[0].full_name == "Foo::bar");
	REQUIRE(en.case_labels[1].full_name == "Foo::baz");
	REQUIRE(en.case_labels[2].full_name == "Foo::quux");
}

TEST_CASE("enum->json", "[json/enum]") {
	auto const result = deduction::parse("../cases/enum-class.hpp");
	auto const jsonString = deduction::convert_parsed_result_to_json(result);
	char const * const expectation = R"json({"items":[{"_type":"enumeration","cases":[{"full_name":"Foo::bar","name":"bar"},{"full_name":"Foo::baz","name":"baz"},{"full_name":"Foo::quux","name":"quux"}],"full_name":"Foo","name":"Foo"}]})json";
	REQUIRE(jsonString == expectation);
}

TEST_CASE("json->enum", "[json/enum]") {
	auto const json = nlohmann::json::parse(R"json({"items":[{"_type":"enumeration","cases":[{"full_name":"Foo::bar","name":"bar"},{"full_name":"Foo::baz","name":"baz"},{"full_name":"Foo::quux","name":"quux"}],"full_name":"Foo","name":"Foo"}]})json");
	auto const results = json.at("items").get<deduction::parse_result>();
	REQUIRE(results.items.size() == 1);

	auto const & en = mpark::get<deduction::enumeration>(results.items[0]);
	REQUIRE(en.name == "Foo");

	REQUIRE(en.case_labels[0].name == "bar");
	REQUIRE(en.case_labels[1].name == "baz");
	REQUIRE(en.case_labels[2].name == "quux");

	REQUIRE(en.case_labels[0].full_name == "Foo::bar");
	REQUIRE(en.case_labels[1].full_name == "Foo::baz");
	REQUIRE(en.case_labels[2].full_name == "Foo::quux");
}
