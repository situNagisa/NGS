if(NGS_BUILD_HPP)
	file(GLOB_RECURSE NGS_BASE_SRC *.hpp)
	target_sources(NGS PRIVATE ${NGS_BASE_SRC})
endif()