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

namespace {
	std::string qualify_name(CXCursor cursor) {
		auto canContinue = [](CXCursor const & tmp) {
			auto kind = clang_getCursorKind(tmp);
			return !clang_Cursor_isNull(tmp)
				&& !clang_isInvalid(kind)
				&& kind != CXCursor_TranslationUnit;
		};

		auto components = std::vector<std::string> {};
		while(canContinue(cursor)) {
			auto cursorSpelling = clang_getCursorSpelling(cursor);
			components.emplace_back(std::string { clang_getCString(cursorSpelling) });
			clang_disposeString(cursorSpelling);
			cursor = clang_getCursorSemanticParent(cursor);
		}

		auto begin = components.begin();
		auto seed = *begin;
		begin++;
		std::string name = std::accumulate(begin, components.end(), seed, [](auto const & accumulated, auto const & next) {
			return next + "::" + accumulated;
		});
		return name;
	}

	CXChildVisitResult visit(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		if (clang_getCursorVisibility(cursor) != CXVisibility_Default)
			return CXChildVisit_Continue;
		if (clang_getCursorAvailability(cursor) != CXAvailability_Available)
			return CXChildVisit_Continue;

		auto location = clang_getCursorLocation(cursor);
		if (!clang_Location_isFromMainFile(location))
			return CXChildVisit_Continue;

		auto kind = clang_getCursorKind(cursor);

		if (clang_isPreprocessing(kind)) {
			std::cout << "preprocessing" << std::endl;
			return CXChildVisit_Continue;
		}

		auto availability = clang_getCursorAvailability(cursor);
		auto language = clang_getCursorLanguage(cursor);
		auto includedFile = clang_getIncludedFile(cursor);
		auto type = clang_getCursorType(cursor);
		auto typeSpelling = clang_getTypeSpelling(type);
		auto underlyingTypedef = clang_getTypedefDeclUnderlyingType(cursor);
		auto spelling = clang_getCursorSpelling(cursor);

		auto usr = clang_getCursorUSR(cursor);
		auto displayName = clang_getCursorDisplayName(cursor);

		std::cout << clang_getCString(spelling)
			<< " of type "
			<< clang_getCString(typeSpelling)
			<< " with usr "
			<< clang_getCString(usr)
			<< " and display name "
			<< clang_getCString(displayName)
			<< " fqdn: "
			<< qualify_name(cursor)
			<< std::endl;
		clang_disposeString(spelling);
		clang_disposeString(typeSpelling);
		clang_disposeString(usr);
		clang_disposeString(displayName);

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
