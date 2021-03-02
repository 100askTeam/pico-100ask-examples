/**
 * Copyright (c) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/*
  我们的7段显示器的针脚如下：

  --A--
  F   B
  --G--
  E   C
  --D--

  默认情况下，我们将GPIO 2分配给A，3分配给B等。
  因此，将GOIP 2连接到7段LED显示屏等上的引脚A。不要忘记使用适当的电阻，最好在每个段上使用一个电阻！
*/

#define PICO_100ASK_FIRST_GPIO      (2)    // 从GP2开始接7段显示器的针脚

// 该数组将数字0-9转换为位模式以发送到GPIO
int bits[10] = {
        0x3f,  // 0
        0x06,  // 1
        0x5b,  // 2
        0x4f,  // 3
        0x66,  // 4
        0x6d,  // 5
        0x7d,  // 6
        0x07,  // 7
        0x7f,  // 8
        0x67   // 9
};


int main() {
    stdio_init_all();
    printf("Hello, 7segment - press button to count down!\n");

    // 为了简单明了这里不使用gpio_set_dir_out_masked()，
    for (int gpio = PICO_100ASK_FIRST_GPIO; gpio < PICO_100ASK_FIRST_GPIO + 7; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);

        // 上面的位图设置了一个位，需要打开一个LED，但是，我们将其拉低以点亮，因此这里反转我们的输出
        gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
    }

    int val = 0;
    while (true) {
        if (val == 9) {
            val = 0;
        } else {
            val++;
        }

        // 我们从GPIO 2开始，我们的位图从0开始，所以从2开始转移。
        int32_t mask = bits[val] << PICO_100ASK_FIRST_GPIO;

        // 使用gpio_set_mask() 一口气设置所有的GPIO
        // 如果其他东西正在使用GPIO，我们可能要使用gpio_put_masked()
        gpio_set_mask(mask);
        sleep_ms(250);
        gpio_clr_mask(mask);
    }

    return 0;
}
