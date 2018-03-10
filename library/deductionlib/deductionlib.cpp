//
//  deductionlib.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "deductionlib.hpp"
#include <clang-c/Index.h>
#include <functional>
#include <iostream>
#include <vector>
#include <numeric>

#include "clang-utility.hpp"
#include "cursor.hpp"
#include "enumeration.hpp"
#include "function.hpp"

namespace {
	using namespace deduction;
	using namespace deduction::clang_utility;

	CXChildVisitResult visit_enum_cases(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto labels = reinterpret_cast<std::vector<enumeration::case_label> *>(client_data);
		labels->emplace_back(get_name(cursor), qualify_name(cursor));
		return CXChildVisit_Continue;
	}

	CXChildVisitResult visit_parameters(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto parameters = reinterpret_cast<std::vector<function::parameter> *>(client_data);
		parameters->emplace_back(get_name(cursor), get_type_name(cursor));
		return CXChildVisit_Continue;
	}

	using lambda_visitor = std::function<CXChildVisitResult(CXCursor &)>;
	CXChildVisitResult visit_lambda(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto lambda = *static_cast<lambda_visitor *>(client_data);
		return lambda(cursor);
	}

	function map_to_function(CXCursor & cursor) {
		std::vector<function::parameter> parameters;
		clang_visitChildren(cursor, visit_parameters, &parameters);
		auto type = clang_getCursorType(cursor);
		auto resultType = clang_getResultType(type);
		return { get_name(cursor), qualify_name(cursor), parameters, map(clang_getTypeSpelling(resultType)) };
	}

	CXChildVisitResult visit(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto items = reinterpret_cast<std::vector<parse_result::item_type> *>(client_data);

		auto wrapper = deduction::cursor { cursor };
		if (wrapper.is_invalid() || !wrapper.is_visible() || !wrapper.is_available() || !wrapper.is_in_main_file() || wrapper.is_preprocessing())
			return CXChildVisit_Continue;

		switch (wrapper.kind())
		{
		case CXCursor_EnumDecl: {
			std::vector<enumeration::case_label> caseLabels;
			clang_visitChildren(cursor, visit_enum_cases, &caseLabels);
			items->push_back(enumeration { wrapper.name(), wrapper.full_name(), std::move(caseLabels) });
			return CXChildVisit_Continue;
		}
		case CXCursor_FunctionDecl: {
			items->emplace_back(map_to_function(cursor));
			return CXChildVisit_Continue;
		}
		default:
			std::cerr << "Unhandled cursor kind: " << wrapper.kind() << " (" << wrapper.type_name() << ")" << std::endl;
		}

		return CXChildVisit_Recurse;
	}
}

namespace deduction {
	std::string const & version = "0.0.1";

	parse_result parse(const std::string & sourcefile) {
		auto index = clang_createIndex(0, 0);
		char const * const args[] = {};
		auto argCount = 0;
		CXUnsavedFile *unsavedFiles = nullptr;
		auto unsavedFileCount = 0;
		auto options = 0;
		auto translationUnit = clang_parseTranslationUnit(index, sourcefile.c_str(), args, argCount, unsavedFiles, unsavedFileCount, options);

		if (!translationUnit)
		{
			std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
			return parse_result {};
		}

		std::vector<parse_result::item_type> items;
		auto cursor = clang_getTranslationUnitCursor(translationUnit);
		clang_visitChildren(cursor, visit, &items);

		clang_disposeTranslationUnit(translationUnit);
		clang_disposeIndex(index);

		return parse_result { items };
	}
}
