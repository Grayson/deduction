cmake_minimum_required(VERSION 3.10)

# Options

option(USE_STATIC_LIBCLANG "Prefer to link static over dynamic linking for libclang" ON)

if(${USE_STATIC_LIBCLANG})
	function(find_static_library RETURN LIBNAME HINTPATH)
		if (WIN32 OR MSVC)
			set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
		elseif (UNIX)
			set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
		endif()
		
		find_library(${RETURN} ${LIBNAME} HINTS ${HINTPATH})
	endfunction()
	
	find_static_library(LIBCLANG clang ../ext/lib)
	
	file(GLOB LLMVLIBS ../ext/lib/*.a)
	list(FILTER LLMVLIBS EXCLUDE REGEX ".*.libclang.a$")
	
	find_library(LIBZ z HINTS /usr/lib/)
	message( STATUS "Found libz: ${LIBZ}")

	find_library(LIBCURSES curses HINTS /usr/lib/)
	message( STATUS "Found libcurses: ${LIBCURSES}" )
	
	set(SYSTEM_LIBRARIES ${LIBZ} ${LIBCURSES})
	set(REQUIRED_LIBRARIES ${SYSTEM_LIBRARIES} ${LLMVLIBS})
else()
	find_library(LIBCLANG clang NAMES libclang.a HINTS ../ext/lib)
	set(REQUIRED_LIBRARIES ${LIBCLANG})
endif()

message( STATUS "Found libclang: ${LIBCLANG}" )

# Project

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
	src/deduction.cpp)

target_include_directories(libdeduction
	INTERFACE include
	PRIVATE include/deduction src ../ext/include)

target_link_libraries(libdeduction PRIVATE ${REQUIRED_LIBRARIES})

install(
	TARGETS libdeduction
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION archive
	PUBLIC_HEADER DESTINATION include)

set_target_properties(libdeduction PROPERTIES 
	CXX_STANDARD 17
	CMAKE_CXX_STANDARD_REQUIRED on
	OUTPUT_NAME "deduction")
