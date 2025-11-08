add_library(potentiometer_lib INTERFACE)

target_sources(potentiometer_lib INTERFACE
    potentiometer.cpp
)

target_include_directories(potentiometer_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This library depends on the Pico SDK's ADC hardware component
target_link_libraries(potentiometer_lib INTERFACE
    pico_stdlib
    hardware_adc
)