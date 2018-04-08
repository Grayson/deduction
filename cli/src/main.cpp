//
//  main.cpp
//  deduction
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <iostream>
#include <deduction/deductionjson.hpp>

char const * const HelpText = R"help(
./deduction [--help] [--pretty|-p] <filepath>
	--help		Print this help text.  This also halts execution.
	--pretty	Optional. Pretty-print JSON output.
	filepath	Required.  Path to a C/C++ header (.h or .hpp) file.
)help";

int main(int argc, const char * argv[]) {
	bool shouldBePretty = false;
	bool shouldPrintHelp = false;
	std::string filepath;

	for (unsigned argIndex = 1; argIndex < argc; argIndex++) {
		auto arg = std::string { argv[argIndex] };
		if (arg == "--pretty" || arg == "-p")
			shouldBePretty = true;
		else
			filepath = std::move(arg);
	}

	if (shouldPrintHelp) {
		std::cout << HelpText << std::endl;
		return 0;
	}

	if (filepath.empty()) {
		std::cerr << "Error: No file specified" << std::endl;
		std::cout << HelpText << std::endl;
		return -1;
	}

	auto options = deduction::json_conversion_options::none;
	if (shouldBePretty)
		options |= deduction::json_conversion_options::pretty_print;

	std::cout << deduction::convert_header_to_json(filepath, options);
	return 0;
}
