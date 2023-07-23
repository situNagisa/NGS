project(unit_test)

file(GLOB_RECURSE srcs "./*.h" "./*.hpp" "./*.c" "./*.cpp")
add_executable(unit_test ${srcs})
target_include_directories(unit_test PRIVATE ${NGS_INCLUDE_DIR})
target_link_directories(unit_test PRIVATE ${NGS_LIBRARY_DIR})
target_link_libraries(unit_test PRIVATE gtest NGS)
set_target_properties(unit_test PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${unit_test_sources})