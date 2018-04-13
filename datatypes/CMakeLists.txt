cmake_minimum_required(VERSION 3.10)

project(datatypes)

add_library(datatypes INTERFACE)

target_include_directories(datatypes INTERFACE include)

install(TARGETS datatypes DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/deduction DESTINATION include)
