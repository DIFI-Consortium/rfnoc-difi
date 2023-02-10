cmake_minimum_required(VERSION 3.12)
project(difipack
    VERSION 0.0.1
    DESCRIPTION "C++ implementation of DIFI packet objects"
    LANGUAGES CXX
)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fPIC)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

add_subdirectory(include/difipack)
add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(test)

option(BUILD_WITH_DOCS "Generate Docs" OFF)
if(BUILD_WITH_DOCS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)
endif()

install(
    TARGETS difipack
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)