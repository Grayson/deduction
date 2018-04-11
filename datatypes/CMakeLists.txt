cmake_minimum_required(VERSION 3.10)

project(datatypes)

add_library(datatypes INTERFACE)

target_include_directories(datatypes INTERFACE include)

install(
	TARGETS datatypes
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)
