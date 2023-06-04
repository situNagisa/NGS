if(NGS_BUILD_HPP)
	file(GLOB_RECURSE NGS_EXTEND_SRC ./*.hpp ./*.cpp)
	target_sources(NGS PUBLIC ${NGS_EXTEND_SRC})
endif()