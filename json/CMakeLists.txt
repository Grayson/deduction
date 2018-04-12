cmake_minimum_required(VERSION 3.10)

project(deductionjson)

add_library(deductionjson
	include/deduction/deductionjson.hpp
	include/deduction/json_conversion_options.hpp
	src/deductionjson.cpp
	src/json_conversion_options.cpp)

target_include_directories(deductionjson
	INTERFACE include
	PRIVATE include/deduction src ../ext/include)

target_link_libraries(deductionjson PRIVATE libdeduction datatypes-json)

install(
	TARGETS deductionjson
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(deductionjson PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deductionjson")
