list(APPEND sources
    packet.cpp
)

include(utils/CMakeLists.txt)
include(prologue/CMakeLists.txt)
include(data_packet/CMakeLists.txt)
include(standard_context_packet/CMakeLists.txt)
include(version_context_packet/CMakeLists.txt)

add_library(difipack ${sources})

target_include_directories(difipack
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PUBLIC $<INSTALL_INTERFACE:include>
)