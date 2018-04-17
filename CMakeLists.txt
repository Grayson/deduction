cmake_minimum_required(VERSION 3.10)

project(deduction)

option(DATATYPES_ONLY "Only builds datatypes and datatypes-json projects." OFF)
option(ENABLE_TESTS "Enables tests [Default: ON]" ON)

add_subdirectory(datatypes)
add_subdirectory(datatypes-json)

if(NOT DATATYPES_ONLY)
	add_subdirectory(library)
	add_subdirectory(json)
	add_subdirectory(cli)
endif()

if(ENABLE_TESTS)
	add_subdirectory(tests)
endif()
