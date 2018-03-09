//
//  deductionlib.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "deductionlib.hpp"
#include <clang-c/Index.h>
#include <iostream>
#include <vector>
#include <numeric>

#include "cursor.hpp"

namespace {
	CXChildVisitResult visit(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto wrapper = deduction::cursor { cursor };
		if (wrapper.is_invalid() || !wrapper.is_visible() || !wrapper.is_available() || !wrapper.is_in_main_file() || !wrapper.is_preprocessing())
			return CXChildVisit_Continue;

		std::cout << wrapper.debug_description() << std::endl;

		return CXChildVisit_Recurse;
	}
}

namespace deduction {
	std::string const & version = "0.0.1";

	bool test() {
		auto index = clang_createIndex(0, 0);
		auto source = "/Volumes/Data/Users/ghansard/Desktop/deduction/library/deductionlib/deductionlib.hpp";
		char const * const args[] = {};
		auto argCount = 0;
		CXUnsavedFile *unsavedFiles = nullptr;
		auto unsavedFileCount = 0;
		auto options = 0;
		auto translationUnit = clang_parseTranslationUnit(index, source, args, argCount, unsavedFiles, unsavedFileCount, options);

		if (!translationUnit)
		{
			std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
			return false;
		}

		auto cursor = clang_getTranslationUnitCursor(translationUnit);
		clang_visitChildren(cursor, visit, nullptr);

		clang_disposeTranslationUnit(translationUnit);
		clang_disposeIndex(index);

		return true;
	}
}
