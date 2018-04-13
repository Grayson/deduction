cmake_minimum_required(VERSION 3.10)

project(deduction)

option(DATATYPES_ONLY "Only builds datatypes and datatypes-json projects." OFF)

message("DATATYPES_ONLY:" ${DATATYPES_ONLY})

add_subdirectory(datatypes)
add_subdirectory(datatypes-json)

if(NOT DATATYPES_ONLY)
	add_subdirectory(library)
	add_subdirectory(json)
	add_subdirectory(cli)
	add_subdirectory(tests)
endif()