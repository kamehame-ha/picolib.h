add_library(liquid_crystal_i2c_lib INTERFACE)

target_sources(liquid_crystal_i2c_lib INTERFACE
    liquid-crystal-i2c.cpp
)

target_include_directories(liquid_crystal_i2c_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(liquid_crystal_i2c_lib INTERFACE
    pico_stdlib
    hardware_i2c
)