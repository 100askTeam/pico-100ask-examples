/**
 * Copyright (c) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// PWM控制电机速度，中断处理程序更新

#include "pico/stdlib.h"


#define PICO_100ASK_MOTOR_IN1_PIN       (1)   // 分配 GP1 给IN1
#define PICO_100ASK_MOTOR_IN2_PIN       (0)   // 分配 GP0 给IN2


int main() {
    gpio_init(PICO_100ASK_MOTOR_IN1_PIN);
    gpio_set_dir(PICO_100ASK_MOTOR_IN1_PIN, GPIO_OUT);

    gpio_init(PICO_100ASK_MOTOR_IN2_PIN);
    gpio_set_dir(PICO_100ASK_MOTOR_IN2_PIN, GPIO_OUT);

   
    while(1){
        // 电机开始转动
        gpio_put(PICO_100ASK_MOTOR_IN1_PIN, 1);
        gpio_put(PICO_100ASK_MOTOR_IN2_PIN, 0);
        sleep_ms(2000);
        // 电机反方向转动
        gpio_put(PICO_100ASK_MOTOR_IN1_PIN, 0);
        gpio_put(PICO_100ASK_MOTOR_IN2_PIN, 1);
        sleep_ms(2000);
        }
}

