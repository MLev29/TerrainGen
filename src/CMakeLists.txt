get_filename_component(TARGET_NAME TerrainGen NAME)

set(SHADER_DIR ${CMAKE_SOURCE_DIR}/workspace/shaders)

file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB TARGET_EXTRA_FILES
	${CMAKE_SOURCE_DIR}/.gitignore
	${CMAKE_SOURCE_DIR}/.gitattributes
	${CMAKE_SOURCE_DIR}/*.md
    ${CMAKE_SOURCE_DIR}/*.txt
)

file (GLOB TARGET_SHADER_FILES
	${SHADER_DIR}/*.vs
	${SHADER_DIR}/*.fs
	${SHADER_DIR}/*.vert
	${SHADER_DIR}/*.frag
	${SHADER_DIR}/*.glsl
)

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})
source_group("shaders" FILES ${TARGET_SHADER_FILES})
source_group("extra files" FILES ${TARGET_EXTRA_FILES})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES} ${TARGET_EXTRA_FILES} ${SHADER_FILES})

target_include_directories(${TARGET_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${DEPENDENCY_LIBRARY} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${TARGET_NAME}
	PRIVATE ${DEPENDENCIES_LIBRARY}
)

if (MSVC)
	# Disable linker warning for glfw3's missing debug info
	target_link_options(${TARGET_NAME} PRIVATE /IGNORE:4099)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)

	# Set workspace directory
	set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/workspace)
endif()