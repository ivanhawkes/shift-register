cmake_minimum_required(VERSION 3.14)

add_executable(shift-register)

target_sources(shift-register PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Main.cpp
        )

# Set a path to our includes.
target_include_directories(shift-register PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# In addition to pico_stdlib required for common PicoSDK functionality, give access to double button reboot.
target_link_libraries(shift-register PUBLIC pico_stdlib hardware_adc
        pico_bootsel_via_double_reset)

pico_add_extra_outputs(shift-register)

# Enable USB *or* UART output.
pico_enable_stdio_usb(shift-register 0)
pico_enable_stdio_uart(shift-register 1)
