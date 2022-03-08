cmake_minimum_required(VERSION 3.10)
project(womf VERSION 1.0.0 LANGUAGES CXX)

macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

file(GLOB WOMF_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/womf/*.cpp")

set_option(BUILD_EXAMPLE TRUE BOOL "TRUE to build the example, FALSE to ignore")

if(NOT WOMF_INCLUDE_DIR)
	set(WOMF_INCLUDE_DIR include)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_compile_definitions(WOMF_STATIC)
add_library(womf-static STATIC ${WOMF_SRC})
target_include_directories(womf-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${WOMF_INCLUDE_DIR})
target_link_libraries(womf-static ${OPT})

if(BUILD_EXAMPLE)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/example)
	add_executable(womf example/womftest.cpp)
	target_include_directories(womf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${WOMF_INCLUDE_DIR})
	target_link_libraries(womf PRIVATE womf-static)
endif()