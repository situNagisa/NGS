cmake_minimum_required(VERSION 3.8)

project(NGS VERSION 0.1)

include(GNUInstallDirs)

set(NGS_CMAKE_ROOT "$ENV{NAGISA_ROOT}/cmake" CACHE PATH "")
include(${NGS_CMAKE_ROOT}/NagisaEnvironment.cmake)

add_subdirectory(src/NGS)
add_subdirectory(test)

option(NAGISA_BUILD_UNIT_TESTS "build unit test" OFF)

if(NAGISA_BUILD_UNIT_TESTS)
	add_subdirectory(unit_test)
endif()

install(
	DIRECTORY ${NGS_SOLUTION_INCLUDE_DIR}/${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)