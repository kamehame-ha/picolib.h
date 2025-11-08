add_library(mcp3008_lib INTERFACE)

target_sources(mcp3008_lib INTERFACE
    mcp3008.cpp
)

target_include_directories(mcp3008_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This library requires the hardware_spi component from the Pico SDK
target_link_libraries(mcp3008_lib INTERFACE
    pico_stdlib
    hardware_spi
)