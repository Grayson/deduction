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
