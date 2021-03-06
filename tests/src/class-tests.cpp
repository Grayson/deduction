//
//  class-tests.cpp
//  tests
//
//  Created by Grayson Hansard on 3/12/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "catch.hpp"
#include <deduction/deduction.hpp>
#include <deduction/datatypes/variant.hpp>

TEST_CASE("simple class", "[class]") {
	auto const result = deduction::parse("../cases/class.hpp");
	auto & st = mpark::get<deduction::structure>(result.items[0]);

	REQUIRE(st.name == "foo");
	REQUIRE(st.full_name == "foo");

	REQUIRE(st.fields.size() == 2);

	REQUIRE(st.fields[0].name == "bar");
	REQUIRE(st.fields[0].type == "int");
	REQUIRE(st.fields[0].is_mutable == true);

	REQUIRE(st.fields[1].name == "corge");
	REQUIRE(st.fields[1].type == "const int");
	REQUIRE(st.fields[1].is_mutable == false);

	REQUIRE(st.methods.size() == 2);
	REQUIRE(st.methods[0].name == "baz");
	REQUIRE(st.methods[0].full_name == "foo::baz");
	REQUIRE(st.methods[0].return_type == "double");
	REQUIRE(st.methods[0].parameters.size() == 2);
	REQUIRE(st.methods[0].parameters[0].name == "quux");
	REQUIRE(st.methods[0].parameters[0].type == "bool");
	REQUIRE(st.methods[0].parameters[1].name == "quuz");
	REQUIRE(st.methods[0].parameters[1].type == "void *");

	REQUIRE(st.methods[1].name == "garply");
	REQUIRE(st.methods[1].full_name == "foo::garply");
	REQUIRE(st.methods[1].return_type == "bool");
	REQUIRE(st.methods[1].parameters.size() == 0);
}

