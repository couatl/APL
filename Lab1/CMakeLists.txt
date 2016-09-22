cmake_minimum_required(VERSION 3.6)

project(hello_world)			

include_directories(include)

set(SOURCE_EXE examples/main.cpp)
		
set(SOURCE_LIB sources/print_hello_world.cpp)			

add_library(print_hello_world STATIC ${SOURCE_LIB})	

add_executable(main ${SOURCE_EXE})	

target_link_libraries(main print_hello_world)		