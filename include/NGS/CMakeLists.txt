option(NGS_BUILD_HPP "Build NGS C++ library" ON)

if(NOT NGS_BUILD_HPP)
	add_definitions(-DNGS_USE_HPP=1)
endif()

add_subdirectory(algorithm)
add_subdirectory(base)
add_subdirectory(embedded)
add_subdirectory(extend)
add_subdirectory(math)

option(NGS_BUILD_NSL "Build NGS NSL library" OFF)
if(NGS_BUILD_NSL)
add_subdirectory(nsl)
endif()

option(NGS_BUILD_NSW "Build NGS NSW library" OFF)
if(NGS_BUILD_NSW)
add_subdirectory(nsw)
endif()