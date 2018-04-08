cmake_minimum_required(VERSION 3.10)

project(deductionjson)

set(PUBLIC_HEADERS
	include/deduction/deductionjson.hpp
	include/deduction/json_conversion_options.hpp)

add_library(deductionjson
	${PUBLIC_HEADERS}
	src/alias.hpp
	src/alias.cpp
	src/deductionjson.cpp
	src/enumeration.cpp
	src/enumeration.hpp
	src/function.cpp
	src/function.hpp
	src/json.hpp
	src/json_conversion_options.cpp
	src/metadata.hpp
	src/metadata.cpp
	src/structure.cpp
	src/structure.hpp
	src/variable.cpp
	src/variable.hpp)

target_include_directories(deductionjson
	INTERFACE include
	PRIVATE include/deduction src ../ext/include)

target_link_libraries(deductionjson PRIVATE libdeduction)

install(
	TARGETS deductionjson
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(deductionjson PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deductionjson")
