if (NOT PICO_NO_HARDWARE)
    add_subdirectory(lm393_adc)
    add_subdirectory(dht11)
    add_subdirectory(hello_7segment)
    add_subdirectory(slide_rheostat)    
    add_subdirectory(motor)
	
endif ()
