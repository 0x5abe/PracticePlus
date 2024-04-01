cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(PracticePlus VERSION 1.0.0)

# source files
file(GLOB_RECURSE SOURCES
	src/hooks/*.cpp
    src/managers/*.cpp
    src/domain/*.cpp
    src/util/*.cpp
	src/*.cpp
    ${OS_SOURCES}
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
      $<$<CONFIG:Debug>:DEBUG>
      $<$<CONFIG:RelWithDebInfo>:DEBUG>
      $<$<CONFIG:Release>:RELEASE>
      $<$<CONFIG:MinSizeRel>:RELEASE>
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src/)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME} EXTERNALS geode.custom-keybinds:1.5.3)