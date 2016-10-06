cmake_minimum_required(VERSION 3.0.2)

project(Lab2)			

include_directories(include)

set(SOURCE_EXE examples/main.cpp)
		
set(SOURCE_LIB sources/prime_check.cpp)			

add_library(prime_check STATIC ${SOURCE_LIB})	

add_executable(main ${SOURCE_EXE})	

add_executable(tests ${TESTS_SOURCE} tests/my_test.cpp)

target_link_libraries(main prime_check)		

