cmake_minimum_required(VERSION 3.14)

find_package(doctest REQUIRED)

add_executable(test test.cxx)
target_link_libraries(
	test PRIVATE
	doctest::doctest
	jlog::jlog
)
