/**
 * Copyright (c) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define PICO_100ASK_DHT_PIN         (15)     // 分配 GP15 给DHT11传感器
#define PICO_100ASK_MAX_TIMINGS     (85)     // 最大时序

typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void read_from_dht(dht_reading *result);

int main() {
    stdio_init_all();
    gpio_init(PICO_100ASK_DHT_PIN);
    gpio_set_dir(PICO_100ASK_DHT_PIN, GPIO_OUT);
    while (1) {
        dht_reading reading;
        read_from_dht(&reading);
        float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
        printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
               reading.humidity, reading.temp_celsius, fahrenheit);

        sleep_ms(2000);
    }
}

void read_from_dht(dht_reading *result) {
    int data[5] = {0, 0, 0, 0, 0};
    uint last = 1;
    uint j = 0;

    gpio_set_dir(PICO_100ASK_DHT_PIN, GPIO_OUT);
    gpio_put(PICO_100ASK_DHT_PIN, 0);
    sleep_ms(20);
    gpio_set_dir(PICO_100ASK_DHT_PIN, GPIO_IN);

    gpio_put(PICO_100ASK_DHT_PIN, 1);
    for (uint i = 0; i < PICO_100ASK_MAX_TIMINGS; i++) {
        uint count = 0;
        while (gpio_get(PICO_100ASK_DHT_PIN) == last) {
            count++;
            sleep_us(1);
            if (count == 255) break;
        }
        last = gpio_get(PICO_100ASK_DHT_PIN);
        if (count == 255) break;

        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1;
            //if (count > 16) data[j / 8] |= 1;
            if (count > 46) data[j / 8] |= 1;
            j++;
        }
    }
    gpio_put(PICO_100ASK_DHT_PIN, 0);

    if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
        result->humidity = (float) ((data[0] << 8) + data[1]) / 10;
        if (result->humidity > 100) {
            result->humidity = data[0];
        }
        result->temp_celsius = (float) (((data[2] & 0x7F) << 8) + data[3]) / 10;
        if (result->temp_celsius > 125) {
            result->temp_celsius = data[2];
        }
        if (data[2] & 0x80) {
            result->temp_celsius = -result->temp_celsius;
        }
    } else {
        printf("Bad data\n");
    }
}
