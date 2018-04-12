cmake_minimum_required(VERSION 3.10)

project(datatypes-json)

add_library(datatypes-json
	include/deduction/json/alias.hpp
	include/deduction/json/enumeration.hpp
	include/deduction/json/function.hpp
	include/deduction/json/json.hpp
	include/deduction/json/structure.hpp
	include/deduction/json/variable.hpp
	src/alias.cpp
	src/enumeration.cpp
	src/function.cpp
	src/metadata.cpp
	src/structure.cpp
	src/variable.cpp)

target_include_directories(datatypes-json
	INTERFACE include
	PRIVATE include/deduction/json src)

target_link_libraries(datatypes-json PRIVATE datatypes)

install(
	TARGETS datatypes-json
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(datatypes-json PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deduction-datatypes-json")