# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(smart_plug_gsm C CXX ASM)
pico_sdk_init()

## FreeRTOS Kernel Config ##
# Include the FreeRTOS kernel and configure it for the ARM M0 port so the examples will compile.
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/libs/FreeRTOS-Kernel)
# set(FREERTOS_PORT GCC_ARM_CM0 CACHE STRING \"\")
# set(FREERTOS_HEAP 4)
# add_library(freertos_config INTERFACE)
# target_include_directories(freertos_config INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}
# )
#add_subdirectory(${FREERTOS_KERNEL_PATH})
# Pull in FreeRTOS
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

add_executable(smart_plug_gsm 
# main
    "${CMAKE_CURRENT_LIST_DIR}/source/main.cpp"
#LED Driver
    "${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/WS2812_Driver.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/WS2812_Driver.h"
#Screen Driver
    "${CMAKE_CURRENT_LIST_DIR}/source/Screen_Driver/ssd1306_i2c_driver.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/Screen_Driver/ssd1306_i2c_driver.h"
    "${CMAKE_CURRENT_LIST_DIR}/source/Screen_Driver/ssd1306_private.h"
    "${CMAKE_CURRENT_LIST_DIR}/source/Screen_Driver/ssd1306_font.h"
)

target_include_directories(smart_plug_gsm PRIVATE 
${CMAKE_CURRENT_LIST_DIR}/source
${CMAKE_CURRENT_LIST_DIR}/resources
${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/
${CMAKE_CURRENT_LIST_DIR}/source/Screen_Driver/
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/generated)
# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(smart_plug_gsm ${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/source/LED_Driver/generated)

target_link_libraries(smart_plug_gsm 
    pico_stdlib 
    hardware_pwm 
    hardware_pio 
    FreeRTOS-Kernel 
    FreeRTOS-Kernel-Heap4
    hardware_i2c
    )
pico_add_extra_outputs(smart_plug_gsm)
