file(GLOB_RECURSE srcs *.cpp)
add_executable(test ${srcs})
target_include_directories(test PRIVATE ${NGS_INCLUDE_DIR})
target_link_directories(test PRIVATE ${NGS_LIBRARY_DIR})
target_link_libraries(test PRIVATE NGS)
set_target_properties(test PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)