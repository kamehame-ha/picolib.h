add_library(mcp23017_lib INTERFACE)

target_sources(mcp23017_lib INTERFACE
    mcp23017.cpp
)

target_include_directories(mcp23017_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mcp23017_lib INTERFACE
    pico_stdlib
    hardware_i2c
)