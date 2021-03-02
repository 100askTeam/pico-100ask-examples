add_executable(motor
        motor.c
        )


# Pull in our pico_stdlib which pulls in commonly used features 
target_link_libraries(motor pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(motor)

# add url via pico_set_program_url
example_auto_set_url(motor)
