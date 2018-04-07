cmake_minimum_required(VERSION 3.10)

project(libdeduction)

set(PUBLIC_HEADERS
	include/alias.hpp
	include/cursor.hpp
	include/deduction.hpp
	include/enumeration.hpp
	include/function.hpp
	include/language.hpp
	include/parse-result.hpp
	include/structure.hpp
	include/variable.hpp
	include/variant.hpp)

add_library(libdeduction
	${PUBLIC_HEADERS}
	src/clang-utility.cpp
	src/clang-utility.hpp
	src/cursor.cpp
	src/deduction.cpp
	src/utility.hpp)

target_include_directories(libdeduction
	PUBLIC include src
	PRIVATE ../ext/include)

# link_directories(../ext/llvm/lib)

find_library(LIBCLANG name clang HINTS ../ext/lib)
MESSAGE( STATUS "Found libclang: ${LIBCLANG}" )

target_link_libraries(libdeduction ${LIBCLANG})

install(TARGETS libdeduction DESTINATION lib)
install(FILES ${PUBLIC_HEADERS} DESTINATION include)

set_target_properties(libdeduction PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deduction")
