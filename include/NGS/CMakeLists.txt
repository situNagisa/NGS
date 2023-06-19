option(NGS_BUILD_HPP "Build NGS C++ library" ON)


set(NGS_SRC)

if(NOT NGS_BUILD_HPP)
	message(STATUS "NGS_BUILD_HPP is OFF, defining NGS_USE_HPP")
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



add_library(nagisa ${NGS_SRC} ${PROJECT_INCLUDE_DIR})

target_include_directories(nagisa 
	PUBLIC 
		${PROJECT_INCLUDE_DIR} 
)

set_target_properties(nagisa PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)