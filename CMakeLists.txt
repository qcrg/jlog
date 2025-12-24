cmake_minimum_required(VERSION 3.14)
project(jlog VERSION 0.0.1 LANGUAGES CXX)

# option(JLOG_BUILD_EXAMPLES "Build jlog examples" OFF)
option(BUILD_TESTING "Build jlog tests" OFF)
option(JLOG_INSTALL "Generate installation target" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(jlog INTERFACE)
add_library(jlog::jlog ALIAS jlog)

target_include_directories(jlog INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(jlog INTERFACE cxx_std_20)

set_target_properties(
	jlog PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(BUILD_TESTING)
	add_subdirectory(test)
endif()

# if(JLOG_BUILD_EXAMPLES)
# 	add_subdirectory(examples)
# endif()

if(JLOG_INSTALL)
	include(GNUInstallDirs)

	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
		jlog-config-version.cmake
	 	VERSION ${PROJECT_VERSION}
		COMPATIBILITY SameMajorVersion
	)

	install(
		FILES ${CMAKE_CURRENT_BINARY_DIR}/jlog-config-version.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jlog
	)

	install(
		FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/jlog.hxx
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
endif()
