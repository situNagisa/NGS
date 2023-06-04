if(NGS_BUILD_HPP)
	file(GLOB_RECURSE NGS_NSL_SRC *.hpp)
	target_sources(NGS PRIVATE ${NGS_NSL_SRC})
endif()