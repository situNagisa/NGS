if(NOT NGS_FIND_COMPONENTS)
	message(STATUS "find_package(NGS) called with no components")
endif()

set(FIND_NGS_PATHS
	"${CMAKE_CURRENT_LIST_DIR}/../.."
	${NAGISA_DIR}
	$ENV{NAGISA_DIR}
	/
	/usr/local
	$ENV{NAGISA_ROOT}
	${NAGISA_ROOT}
)

#update required components
set(__find_ngs_base_dependencies		"")
set(__find_ngs_extend_dependencies		"")
set(__find_ngs_math_dependencies		"")
set(__find_ngs_algorithm_dependencies	"")
set(__find_ngs_embedded_dependencies	"")
set(__find_ngs_graphic_dependencies		"")
set(__find_ngs_imgui_dependencies		"")
set(__find_ngs_ngl_dependencies			"")
set(__find_ngs_nda_dependencies			"")
set(__find_ngs_nsl_dependencies			"")
set(__find_ngs_nsw_dependencies			"")
set(__find_ngs_additional_components "")
foreach(component ${NGS_FIND_COMPONENTS})
	string(TOLOWER ${component} component_lower)
	list(APPEND __find_ngs_additional_components __find_ngs_${component_lower}_dependencies)
endforeach()
list(APPEND NGS_FIND_COMPONENTS ${__find_ngs_additional_components})
list(REMOVE_DUPLICATES NGS_FIND_COMPONENTS)

#config target
if(NGS_STATIC_LIBRARIES)
	set(__config_name "Static")
else()
	set(__config_name "Shared")
endif()
set(__target_config_file "${CMAKE_CURRENT_BINARY_DIR}/NGS${__config_name}Target.cmake")
if(NOT EXISTS ${__target_config_file})
	set(FIND_NGS_ERROR "required NGS configuration (${__target_config_file}) was not found")
	set(NGS_FOUND FALSE)
endif()

set(NGS_FOUND TRUE)


foreach(component ${FIND_NGS_COMPONENTS})
	string(TOUPPER ${component} component_upper)
	if(TARGET ngs-${component})
		set(NGS_${component_upper}_FOUND)
	else()
		set(FIND_NGS_ERROR "found NGS but requested component (${component}) is missing in the config defined in ${NGS_DIR}.")
	endif()
endforeach()

if(NGS_FOUND)
	message(STATUS "Found NGS: ${NGS_DIR}")
else()
	message(FATAL_ERROR "NGS was not found: ${FIND_NGS_ERROR}")
endif()