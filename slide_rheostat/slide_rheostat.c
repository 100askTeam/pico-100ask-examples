/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define PICO_100ASK_SLIDE_RHEOSTAT_PIN     (26)   // 分配 GP26 用于ADC检测


int main() {
    stdio_init_all();
    adc_init();

    // 确保GPIO高阻抗，无上拉等
    adc_gpio_init(PICO_100ASK_SLIDE_RHEOSTAT_PIN);

    while (true) {
        adc_select_input(0);
        uint adc_x_raw = adc_read();
        printf("value: %d\nVoltage: %fV\n", adc_x_raw, (float)(adc_x_raw * (3.3/4096)));
        sleep_ms(500);
    }
}
