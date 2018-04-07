cmake_minimum_required(VERSION 3.10)

project(libdeduction)

set(PUBLIC_HEADERS
	include/deduction/alias.hpp
	include/deduction/deduction.hpp
	include/deduction/enumeration.hpp
	include/deduction/function.hpp
	include/deduction/language.hpp
	include/deduction/parse-result.hpp
	include/deduction/structure.hpp
	include/deduction/utility.hpp
	include/deduction/variable.hpp
	include/deduction/variant.hpp)

add_library(libdeduction
	${PUBLIC_HEADERS}
	src/clang-utility.cpp
	src/clang-utility.hpp
	src/deduction.cpp
	src/utility.hpp)

target_include_directories(libdeduction
	INTERFACE include
	PRIVATE include/deduction src ../ext/include)

find_library(LIBCLANG name clang HINTS ../ext/lib)
MESSAGE( STATUS "Found libclang: ${LIBCLANG}" )

target_link_libraries(libdeduction ${LIBCLANG})

install(TARGETS libdeduction DESTINATION lib)
install(FILES ${PUBLIC_HEADERS} DESTINATION include)

set_target_properties(libdeduction PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deduction")
