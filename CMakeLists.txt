cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_project C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pico_sdk_init()

# The VS Code extension section is fine to keep as is.
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

add_subdirectory(ht16k33)
add_subdirectory(mcp23017)
add_subdirectory(liquid-crystal-i2c)
add_subdirectory(mcp3008)
add_subdirectory(potentiometer)

add_executable(pico_app
    test.cpp
)

target_link_libraries(pico_app PRIVATE
    pico_stdlib
    ht16k33_lib
    liquid_crystal_i2c_lib
    mcp3008_lib
    potentiometer_lib
    # tinyusb_device
    # tinyusb_board
)

pico_add_extra_outputs(pico_app)

pico_enable_stdio_usb(pico_app 1)
pico_enable_stdio_uart(pico_app 0)