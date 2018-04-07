cmake_minimum_required(VERSION 3.10)

project(deductionjson)

set(PUBLIC_HEADERS
	include/deductionjson.hpp
	include/json_conversion_options.hpp)

add_library(deductionjson
	${PUBLIC_HEADERS}
	src/alias.hpp
	src/alias.cpp
	src/enumeration.cpp
	src/enumeration.hpp
	src/function.cpp
	src/function.hpp
	src/deductionjson.cpp
	src/json.hpp
	src/json_conversion_options.cpp
	src/structure.cpp
	src/structure.hpp
	src/variable.cpp
	src/variable.hpp)

target_include_directories(deductionjson
	PUBLIC include
	PRIVATE src)
target_link_libraries(deductionjson PRIVATE libdeduction)

install(TARGETS deductionjson DESTINATION lib)
install(FILES ${PUBLIC_HEADERS} DESTINATION include/deduction)

set_target_properties(deductionjson PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deductionjson")
