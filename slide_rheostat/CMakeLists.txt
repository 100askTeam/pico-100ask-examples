add_executable(slide_rheostat
        slide_rheostat.c
        )


pico_enable_stdio_usb(slide_rheostat 1)
pico_enable_stdio_uart(slide_rheostat 1)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(slide_rheostat pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(slide_rheostat)

# add url via pico_set_program_url
example_auto_set_url(slide_rheostat)
