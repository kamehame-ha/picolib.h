add_library(ht16k33_lib INTERFACE)

target_sources(ht16k33_lib INTERFACE
    ht16k33.cpp
)

target_include_directories(ht16k33_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ht16k33_lib INTERFACE
    pico_stdlib
    hardware_i2c
)