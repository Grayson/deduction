//
//  deductionlib.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include "deduction.hpp"
#include <clang-c/Index.h>
#include <functional>
#include <iostream>
#include <vector>
#include <numeric>

#include <deduction/datatypes/enumeration.hpp>
#include <deduction/datatypes/function.hpp>
#include "clang-utility.hpp"

namespace {
	using namespace deduction;
	using namespace deduction::clang_utility;

	enum class accessibility {
		acc_private,
		acc_public,
	};

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

	structure::field map_to_struct_field(CXCursor & cursor) {
		return { get_name(cursor), get_type_name(cursor), clang_isConstQualifiedType(clang_getCursorType(cursor)) == 0 };
	}

	structure map_to_structure(CXCursor cursor, accessibility defaultAccessibility) {
		std::vector<structure::field> fields;
		std::vector<function> methods;
		std::vector<function> constructors;
		auto currentAccessibility = defaultAccessibility;

		lambda_visitor test = [&](CXCursor & child) {
			auto childKind = clang_getCursorKind(child);
			switch(childKind) {
			case CXCursor_FieldDecl: {
				if (currentAccessibility == accessibility::acc_public)
					fields.emplace_back(map_to_struct_field(child));
				return CXChildVisit_Continue;
			}
			case CXCursor_CXXMethod: {
				if (currentAccessibility == accessibility::acc_public)
					methods.emplace_back(map_to_function(child));
				return CXChildVisit_Continue;
			}
			case CXCursor_CXXAccessSpecifier: {
				currentAccessibility = CX_CXXPublic == clang_getCXXAccessSpecifier(child)
					? accessibility::acc_public
					: accessibility::acc_private;
				return CXChildVisit_Continue;
			}
			case CXCursor_Constructor: {
				if (currentAccessibility == accessibility::acc_public)
					constructors.emplace_back(map_to_function(child));
				return CXChildVisit_Continue;
			}
			case CXCursor_Destructor: {
				// Although theoretically possible to delete the destructor,
				// that's considered unwise.
				return CXChildVisit_Continue;
			}
			default:
				std::cerr << "Unhandled structure child kind: " << childKind << std::endl;
				return CXChildVisit_Continue;
			}
		};
		clang_visitChildren(cursor, visit_lambda, &test);
		return { get_name(cursor), qualify_name(cursor), std::move(fields), std::move(methods), std::move(constructors) };
	}

	alias map_to_alias(CXCursor & cursor) {
		auto type = clang_getCursorType(cursor);
		std::string underlyingType = get_name(clang_getTypedefDeclUnderlyingType(cursor));
		std::string typedefName = map(clang_getTypedefName(type));
		return { std::move(typedefName), std::move(underlyingType) };
	}

	variable map_to_variable(CXCursor & cursor) {
		auto const type = get_type_name(cursor);
		auto const typeWithoutModifiers = remove_type_qualifiers(type);
		return {
			get_name(cursor),
			std::move(type),
			std::move(typeWithoutModifiers),
			clang_isConstQualifiedType(clang_getCursorType(cursor)) == 0,
			clang_getCursorLinkage(cursor) == CXLinkage_External
		};
	}

	bool is_visible(CXCursor const & cursor) {
		return CXVisibility_Default == clang_getCursorVisibility(cursor);
	}

	bool is_available(CXCursor const & cursor) {
		return CXAvailability_Available == clang_getCursorAvailability(cursor);
	}

	bool is_in_main_file(CXCursor const & cursor) {
		return clang_Location_isFromMainFile(clang_getCursorLocation(cursor));
	}

	bool is_preprocessing(CXCursor const & cursor) {
		return clang_isPreprocessing(clang_getCursorKind(cursor));
	}

	bool is_invalid(CXCursor const & cursor) {
		return clang_isInvalid(clang_getCursorKind(cursor));
	}

	CXChildVisitResult visit(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto items = reinterpret_cast<std::vector<parse_result::item_type> *>(client_data);

		if (is_invalid(cursor) || !is_visible(cursor) || !is_available(cursor) || !is_in_main_file(cursor) || is_preprocessing(cursor))
			return CXChildVisit_Continue;

		switch (clang_getCursorKind(cursor))
		{
		case CXCursor_ClassDecl: {
			items->emplace_back(map_to_structure(cursor, accessibility::acc_private));
			return CXChildVisit_Continue;
		}
		case CXCursor_EnumDecl: {
			std::vector<enumeration::case_label> caseLabels;
			clang_visitChildren(cursor, visit_enum_cases, &caseLabels);
			items->push_back(enumeration { get_name(cursor), qualify_name(cursor), std::move(caseLabels) });
			return CXChildVisit_Continue;
		}
		case CXCursor_FunctionDecl: {
			items->emplace_back(map_to_function(cursor));
			return CXChildVisit_Continue;
		}
		case CXCursor_StructDecl: {
			items->emplace_back(map_to_structure(cursor, accessibility::acc_public));
			return CXChildVisit_Continue;
		}
		case CXCursor_TypeAliasDecl: {
			items->emplace_back(map_to_alias(cursor));
			return CXChildVisit_Continue;
		}
		case CXCursor_VarDecl: {
			items->emplace_back(map_to_variable(cursor));
			return CXChildVisit_Continue;
		}
		case CXCursor_Namespace: {
			return CXChildVisit_Recurse;
		}
		default:
			std::cerr << "Unhandled cursor kind: " << clang_getCursorKind(cursor) << " (" << get_type_name(cursor) << ")" << std::endl;
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
