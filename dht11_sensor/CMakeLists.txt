add_executable(dht11
        dht11.c
        )

pico_enable_stdio_usb(dht11 1)
pico_enable_stdio_uart(dht11 1)

target_link_libraries(dht11 pico_stdlib)

pico_add_extra_outputs(dht11)

# add url via pico_set_program_url
example_auto_set_url(dht11)

