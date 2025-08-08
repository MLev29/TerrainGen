# Root CMake
cmake_minimum_required(VERSION 3.25)

project(TerrainGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(dependencies)
add_subdirectory(src)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TerrainGen)
endif()

if (NOT EXISTS {CMAKE_SOURCE_DIR}/workspace)
    message("Failed to locate workspace directory, attempting to creating directory...")
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/workspace)
endif()