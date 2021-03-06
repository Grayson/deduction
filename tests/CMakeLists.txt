cmake_minimum_required(VERSION 3.10)

file(GLOB files "src/*.cpp")
foreach(file ${files})
	get_filename_component(TESTFILENAME ${file} NAME_WE)

	if(${TESTFILENAME} STREQUAL main)
		continue()
	endif()
	
	set(TESTNAME test-${TESTFILENAME})
	
	add_executable(${TESTNAME}
		src/catch.hpp
		src/main.cpp
		${file})

	target_link_libraries(${TESTNAME} PRIVATE libdeduction deductionjson datatypes-json)
	set_target_properties(${TESTNAME} PROPERTIES
		CXX_STANDARD 17
		CMAKE_CXX_STANDARD_REQUIRED on
		OUTPUT_NAME ${TESTNAME})

	add_test(${TESTNAME} ${TESTNAME})
	
endforeach()

file(COPY cases DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
