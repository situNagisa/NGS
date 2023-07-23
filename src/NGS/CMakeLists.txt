function(__NGS_register_components component_id default_state)
	set(options)
	set(single_value)
	set(multi_value libraries)
	cmake_parse_arguments(_ "${options}" "${single_value}" "${multi_value}" ${ARGN})

	string(TOUPPER ${component_id} component_id_upper)

	set(__definitions NGS_USE_${component_id_upper})

	option(COMPONENT_${component_id} "Enable use of component ${component_id}" ${default_state})
	
	if(COMPONENT_${component_id})
		set(NGS_${PROJECT_NAME}_COMPONENTS ${NGS_${PROJECT_NAME}_COMPONENTS} ${component_id_upper} PARENT_SCOPE)
		set(NGS_${PROJECT_NAME}_${component_id_upper}_INCLUDE_DIR ${NGS_INCLUDE_DIR}/ PARENT_SCOPE)
		set(NGS_${PROJECT_NAME}_${component_id_upper}_LIBRARIES ${__libraries} PARENT_SCOPE)
		set(NGS_${PROJECT_NAME}_${component_id_upper}_DEFINITIONS ${__definitions} PARENT_SCOPE)
	endif()
endfunction()

# option(NGS_USE_HPP "Enable use of hpp" OFF)

__NGS_register_components(base			ON		libraries	)
__NGS_register_components(extend		ON		libraries	)
__NGS_register_components(math			ON		libraries	)
__NGS_register_components(algorithm		ON		libraries	)
__NGS_register_components(graphic		OFF		libraries	)
__NGS_register_components(nda			OFF		libraries	)
__NGS_register_components(imgui			OFF		libraries	imgui)
__NGS_register_components(ngl			OFF		libraries	opengl)
__NGS_register_components(nsl			OFF		libraries	)
__NGS_register_components(nsw			OFF		libraries	)
__NGS_register_components(esp			OFF		libraries	)

function(import_nagisa target)
	set(__cpp_data "")
	set(__include_dirs "")
	set(__sources "")
	set(__libraries "")
	set(__definitions "")
	foreach(component ${NGS_${PROJECT_NAME}_COMPONENTS})
		string(TOLOWER ${component} component_lower)
		
		set(__cpp_data "${__cpp_data}#include \"NGS/${component_lower}/${component_lower}.hpp\"\n")
		list(APPEND __include_dirs ${NGS_${PROJECT_NAME}_${component}_INCLUDE_DIR})
		list(APPEND __libraries ${NGS_${PROJECT_NAME}_${component}_LIBRARIES})
		list(APPEND __definitions ${NGS_${PROJECT_NAME}_${component}_DEFINITIONS})
	endforeach()
	if(NGS_USE_HPP)
		list(APPEND __definitions NGS_USE_HPP)
	else()
		file(WRITE ${NGS_SOURCE_DIR}/${PROJECT_NAME}/NGS.cpp ${__cpp_data})
		list(APPEND __sources ${NGS_SOURCE_DIR}/${PROJECT_NAME}/NGS.cpp)
	endif()

	NGS_set_target_properties(${target}
		include_dirs ${__include_dirs}
		library_dirs ${NGS_LIBRARY_DIR}
		libraries ${__libraries}
		definitions ${__definitions}
		sources ${__sources}
	)
	set_target_properties(${target} PROPERTIES
		CMAKE_CXX_STANDARD 20
	)
endfunction()

set(target NGS)
set(lib_type STATIC)

set(__cpp_data "")
set(__include_dirs "")
set(__libraries "")
set(__definitions "")
foreach(component ${NGS_${PROJECT_NAME}_COMPONENTS})
	string(TOLOWER ${component} component_lower)
		
	set(__cpp_data "${__cpp_data}#include \"NGS/${component_lower}/${component_lower}.hpp\"\n")
	list(APPEND __include_dirs ${NGS_${PROJECT_NAME}_${component}_INCLUDE_DIR})
	list(APPEND __libraries ${NGS_${PROJECT_NAME}_${component}_LIBRARIES})
	list(APPEND __definitions ${NGS_${PROJECT_NAME}_${component}_DEFINITIONS})
endforeach()

list(REMOVE_DUPLICATES __include_dirs)
list(REMOVE_DUPLICATES __libraries)
list(REMOVE_DUPLICATES __definitions)

file(WRITE ./NGS.cpp ${__cpp_data})
file(GLOB_RECURSE __sources *.cpp)

add_library(${target} ${lib_type} ${__sources})
target_include_directories(${target} PRIVATE ${__include_dirs})
target_link_directories(${target} PRIVATE ${NGS_LIBRARY_DIR})
target_link_libraries(${target} PRIVATE ${__libraries})
target_compile_definitions(${target} PUBLIC ${__definitions})
set_target_properties(${target} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX ${NGS_INSTALL_DIR})
endif()

install(
	TARGETS ${target}
	EXPORT ${target}Config
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
	EXPORT ${target}Config
	NAMESPACE ${target}::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${target}"
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion
)
install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${target}"
)
