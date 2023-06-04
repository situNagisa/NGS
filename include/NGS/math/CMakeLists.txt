if(NGS_BUILD_HPP)
	file(GLOB_RECURSE NGS_MATH_SRC *.hpp)
	target_sources(NGS PRIVATE ${NGS_MATH_SRC})
endif()